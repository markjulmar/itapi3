using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using JulMar.Tapi3;
using QuartzTypeLib;
using System.IO;
using System.Reflection;

namespace OutgoingSample
{
    public partial class OutgoingForm : Form
    {
        TCall currCall = null;
        TTerminal playbackTerminal = null;
        string PLAY_FILENAME;

        public OutgoingForm()
        {
            InitializeComponent();
        }

        private void OnLoad(object sender, EventArgs e)
        {
            PLAY_FILENAME = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location) + @"\welcome.wav";

            // Initialize TAPI
            if (tapi.Initialize() == 0)
            {
                MessageBox.Show("No TAPI devices available.");
                OnExit(this, EventArgs.Empty);
            }

            // Populate destination types
            cbDestinationType.Items.AddRange(new object[] {
                    LINEADDRESSTYPES.SDP,
                    LINEADDRESSTYPES.EmailName,
                    LINEADDRESSTYPES.DomainName,
                    LINEADDRESSTYPES.PhoneNumber,
                    LINEADDRESSTYPES.IPAddress
                    });

            // Populate our address combo box with all the available addresses.
            foreach (TAddress addr in tapi.Addresses)
            {
                // Add each voice-capable address
                if ((addr.MediaTypes & TAPIMEDIATYPES.AUDIO) != 0)
                    cbAddress.Items.Add(addr);
            }

            cbAddress.SelectedIndex = 0;
            cbDestinationType.SelectedIndex = 0;
        }

        private void OnDial(object sender, EventArgs e)
        {
            TAddress addr = (TAddress)cbAddress.SelectedItem;
            LINEADDRESSTYPES addrType = (LINEADDRESSTYPES) cbDestinationType.SelectedItem;

            TAPIMEDIATYPES mediaType = TAPIMEDIATYPES.AUDIO;
            if (addr.QueryMediaType(TAPIMEDIATYPES.VIDEO))
                mediaType |= TAPIMEDIATYPES.VIDEO;

            try
            {
                addr.Open(mediaType);
            }
            catch (TapiException ex)
            {
                // Invalid media mode? Try just datamodem for unimodem.
                if (ex.ErrorCode == unchecked((int)0x80040004))
                {
                    try 
                    { 
                        addr.Open(TAPIMEDIATYPES.DATAMODEM);  
                    }
                    catch
                    {
                        toolStripStatusLabel1.Text = ex.Message;
                    }
                }
                else
                {
                    toolStripStatusLabel1.Text = ex.Message;
                }
            }

            // Create a call -- this should always succeed
            currCall = addr.CreateCall(textDestination.Text, addrType, mediaType);
            if (currCall != null)
            {
                // Get the playback terminal from the call
                try
                {
                    playbackTerminal = currCall.RequestTerminal(
                        TTerminal.FilePlaybackTerminal,
                        TAPIMEDIATYPES.AUDIO, TERMINAL_DIRECTION.TD_CAPTURE);
                    if (playbackTerminal != null)
                    {
                        playbackTerminal.MediaPlayList = new string[] { PLAY_FILENAME };
                        //string[] names = playbackTerminal.MediaPlayList;
                        //playbackTerminal.Name;
                        //currCall.SelectTerminalOnCall(playbackTerminal);
                    }
                    else
                    {
                        MessageBox.Show("Failed to retrieve playback terminal.");
                    }
                }
                catch (TapiException ex)
                {
                    MessageBox.Show(ex.Message);
                }


                //// If the address supports media streams, then select terminals on it.
                //if (addr.SupportsMediaStreams)
                //{
                //    // This walks through the streams of the call and selects the default terminal
                //    // for each one.
                //    currCall.SelectDefaultTerminals();
                //}

                try
                {
                    // Connect the call
                    currCall.Connect(false);
                    toolStripStatusLabel1.Text = "Placing call...";
                }
                catch (TapiException ex)
                {
                    toolStripStatusLabel1.Text = ex.Message;
                }
            }
        }

        private void OnDisconnect(object sender, EventArgs e)
        {
            if (currCall != null)
            {
                try
                {
                    currCall.Disconnect(DISCONNECT_CODE.DC_NORMAL);
                }
                catch (TapiException ex)
                {
                    toolStripStatusLabel1.Text = ex.Message;
                }
            }
        }

        private void OnExit(object sender, EventArgs e)
        {
            this.Close();
        }

        private void OnNewCall(object sender, TapiCallNotificationEventArgs e)
        {
            TCall newCall = e.Call;

            // If we are the owner of the call..
            if (newCall.Privilege == CALL_PRIVILEGE.CP_OWNER)
            {
                if (currCall != newCall)
                {
                    try
                    {
                        newCall.Disconnect(DISCONNECT_CODE.DC_REJECTED);
                    }
                    catch (TapiException ex)
                    {
                        toolStripStatusLabel1.Text = ex.Message;
                    }
                }
                else
                {
                    toolStripStatusLabel1.Text = "Call " + newCall.ToString();
                }
            }
        }

        private void OnCallStateChanged(object sender, TapiCallStateEventArgs e)
        {
            TCall thisCall = e.Call;
            if (thisCall == currCall)
            {
                toolStripStatusLabel1.Text = "Call " + currCall.ToString();
                if (e.State == CALL_STATE.CS_DISCONNECTED)
                {
                    currCall = null;
                    thisCall.Address.Close();
                }
                CheckControls();
            }
        }

        private void OnMediaEvent(object sender, TapiCallMediaEventArgs e)
        {
            // When the video rendering stream activates, popup the video window if it's available.
            if (e.Event == CALL_MEDIA_EVENT.CME_STREAM_ACTIVE)
            {
                TStream stm = e.Stream;
                if (stm.Direction == TERMINAL_DIRECTION.TD_RENDER &&
                    stm.MediaType == TAPIMEDIATYPES.VIDEO)
                {
                    TTerminal t = stm.FindTerminal(stm.MediaType, stm.Direction);
                    if (t != null)
                    {
                        IVideoWindow vw = t.QueryInterface(typeof(IVideoWindow)) as IVideoWindow;
                        if (vw != null)
                        {
                            // Position to the right
                            vw.SetWindowPosition(this.Left + this.Width + 2, this.Top, vw.Width, vw.Height);
                            vw.Visible = 1;
                        }
                    }
                }
                else if (currCall != null && 
                    stm.Direction == TERMINAL_DIRECTION.TD_CAPTURE &&
                    stm.MediaType == TAPIMEDIATYPES.AUDIO &&
                    playbackTerminal != null)
                {
                    try
                    {
                        playbackTerminal.Start();
                        toolStripStatusLabel1.Text = "File Playback Terminal started ";
                    }
                    catch (TapiException ex)
                    {
                        MessageBox.Show(ex.Message);
                    }

                }
            }
        }

        private void OnClose(object sender, FormClosingEventArgs e)
        {
            // Shutdown TAPI
            tapi.Shutdown();
        }

        private void Destination_TextChanged(object sender, EventArgs e)
        {
            CheckControls();
        }

        private void cbAddress_SelectedIndexChanged(object sender, EventArgs e)
        {
            CheckControls();
        }

        private void cbDestination_SelectedIndexChanged(object sender, EventArgs e)
        {
            CheckControls();
        }

        private void CheckControls()
        {
            btnDisconnect.Enabled = currCall != null;

            if (cbDestinationType.SelectedIndex >= 0 &&
                textDestination.Text.Length > 0 &&
                cbAddress.SelectedIndex >= 0)
            {
                TAddress addr = (TAddress)cbAddress.SelectedItem;
                LINEADDRESSTYPES addrType = (LINEADDRESSTYPES) cbDestinationType.SelectedItem;
                
                btnDial.Enabled = (currCall == null && (addr.get_AddressCapability(ADDRESS_CAPABILITY.AC_ADDRESSTYPES) & (int)addrType) != 0);
            }
            else
                btnDial.Enabled = false;
        }

        private void OnFileTerminal(object sender, TapiFileTerminalEventArgs e)
        {
            // We are interested in TMS_IDLE because we will un-select playback and 
            // select recording
            if (e.State == TERMINAL_MEDIA_STATE.TMS_IDLE)
            {
                if (e.Terminal.Direction == TERMINAL_DIRECTION.TD_RENDER && 
                    playbackTerminal != null)
                {
                    try
                    {
                        // Remove the playback terminal
                        currCall.UnselectTerminalOnCall(playbackTerminal);
                        playbackTerminal.Dispose();
                        playbackTerminal = null;

                        // Generate a custom tone on the call.
                        currCall.GenerateCustomTones(new TCustomTone[] { new TCustomTone(700, 500, 0, 0xFFFF) }, 500);

                        // Disconnect the call
                        currCall.Disconnect(DISCONNECT_CODE.DC_NORMAL);
                    }
                    catch (TapiException ex)
                    {
                        MessageBox.Show(ex.Message);
                        currCall.Disconnect(DISCONNECT_CODE.DC_NORMAL);
                    }
                }
            }
        }
    }
}