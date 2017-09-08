using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Reflection;
using JulMar.Tapi3;
using System.IO;

namespace AnsMachine
{
    public partial class AutoAttendantForm : Form
    {
        TCall activeCall = null;
        TTerminal playbackTerminal = null;
        string PLAY_FILENAME;

        public AutoAttendantForm()
        {
            InitializeComponent();
        }

        private void Form_Load(object sender, EventArgs e)
        {
            PLAY_FILENAME = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location) + @"\welcome.wav";

            tTapi.Initialize();
            foreach (TAddress addr in tTapi.Addresses)
            {
                if (addr.QueryMediaType(TAPIMEDIATYPES.AUDIO))
                {
                    try
                    {
                        addr.Open(TAPIMEDIATYPES.AUDIO);
                    }
                    catch (TapiException ex)
                    {
                        if (ex.ErrorCode == unchecked((int)0x80040004))
                        {
                            try
                            {
                                addr.Open(TAPIMEDIATYPES.DATAMODEM);
                            }
                            catch
                            {
                            }
                        }
                    }
                }
            }
            DisconnectCall();
        }

        private void Form_Closing(object sender, FormClosingEventArgs e)
        {
            tTapi.Shutdown();
        }

        private void SetStatusMessage(string msg)
        {
            textStatus.Text = msg;
        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void OnCallMedia(object sender, TapiCallMediaEventArgs e)
        {
            try 
            {
                if (activeCall != null && e.Event == CALL_MEDIA_EVENT.CME_STREAM_ACTIVE &&
                    e.Terminal.Direction == TERMINAL_DIRECTION.TD_CAPTURE &&
                    playbackTerminal != null)
                {
                    playbackTerminal.Start();
                    SetStatusMessage("File Playback Terminal started ");
                }
            }
            catch (TapiException ex)
            {
                MessageBox.Show(ex.Message);
                activeCall.Disconnect(DISCONNECT_CODE.DC_NORMAL);
            }
        }

        private void OnNewCall(object sender, TapiCallNotificationEventArgs e)
        {
            TCall thisCall = e.Call;
            if (thisCall.Privilege == CALL_PRIVILEGE.CP_OWNER)
            {
                if (activeCall != null)
                    thisCall.Disconnect(DISCONNECT_CODE.DC_REJECTED);
                else
                    activeCall = thisCall;
            }
        }

        private void OnCallState(object sender, TapiCallStateEventArgs e)
        {
            TCall thisCall = e.Call;
            if (thisCall == activeCall)
            {
                switch (thisCall.CallState)
                {
                    case CALL_STATE.CS_CONNECTED:
                        HandleCall();
                        break;
                    case CALL_STATE.CS_DISCONNECTED:
                        DisconnectCall();
                        break;
                    case CALL_STATE.CS_OFFERING:
                        AnswerCall();
                        break;
                    default:
                        break;
                }
            }
        }

        private void DisconnectCall()
        {
            SetStatusMessage("Waiting for a call...");
            if (activeCall != null)
            {
                activeCall.Dispose();
                activeCall = null;
            }
        }

        private void HandleCall()
        {
            SetStatusMessage("Connected; waiting for file playback terminal to run...");
        }

        private void AnswerCall()
        {
            SetStatusMessage("Answering Call...");
            if (playbackTerminal != null)
            {
                playbackTerminal.Dispose();
                playbackTerminal = null;
            }

            // Get the playback terminal from the call
            try
            {
                playbackTerminal = activeCall.RequestTerminal(TTerminal.FilePlaybackTerminal, 
                            TAPIMEDIATYPES.AUDIO, TERMINAL_DIRECTION.TD_CAPTURE);
                if (playbackTerminal != null)
                {
                    playbackTerminal.MediaPlayList = new string[] { PLAY_FILENAME };
                    activeCall.SelectTerminalOnCall(playbackTerminal);
                    activeCall.Answer();
                }
                else
                {
                    MessageBox.Show("Failed to retrieve playback terminal.");
                    activeCall.Disconnect(DISCONNECT_CODE.DC_REJECTED);
                }
            }
            catch (TapiException ex)
            {
                MessageBox.Show(ex.Message);
                activeCall.Disconnect(DISCONNECT_CODE.DC_NORMAL);
            }
        }

        private void OnFileTerminal(object sender, TapiFileTerminalEventArgs e)
        {
            // We are interested in TMS_IDLE because we will un-select playback and 
            // select recording
            if (e.State == TERMINAL_MEDIA_STATE.TMS_IDLE)
            {
                if (e.Terminal.Direction == TERMINAL_DIRECTION.TD_CAPTURE && playbackTerminal != null)
                {
                    try
                    {
                        // Remove the playback terminal
                        activeCall.UnselectTerminalOnCall(playbackTerminal);
                        playbackTerminal.Dispose();
                        playbackTerminal = null;

                        // Generate a custom tone on the call.
                        activeCall.GenerateCustomTones(new TCustomTone[] { new TCustomTone(700, 500, 0, 0xFFFF) }, 500);

                        // Disconnect the call
                        activeCall.Disconnect(DISCONNECT_CODE.DC_NORMAL);
                    }
                    catch (TapiException ex)
                    {
                        MessageBox.Show(ex.Message);
                        activeCall.Disconnect(DISCONNECT_CODE.DC_NORMAL);
                    }
                }
            }
        }
    }
}