using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using JulMar.Tapi3;

namespace ConversationRecord
{
    public partial class ConversationRecordForm : Form
    {
        static readonly string MESSAGE_PROMPT = Environment.CurrentDirectory + @"\sample.wav";

        TTapi tTapi = new TTapi();
        TAddress selectedAddress;
        TCall currCall;
        TTerminal playbackTerminal, recordTerminal;

        public ConversationRecordForm()
        {
            InitializeComponent();
            InitializeTapi();
        }

        private void InitializeTapi()
        {
            try
            {
                if (tTapi.Initialize() == 0)
                {
                    MessageBox.Show("No TAPI devices available.");
                    this.Close();
                }

                tTapi.TE_CALLSTATE += new EventHandler<TapiCallStateEventArgs>(tapi_TE_CALLSTATE);

                // Add all the voice-capable lines.
                comboBox1.Items.AddRange(
                    Array.FindAll(tTapi.Addresses,
                            delegate(TAddress addr) 
                            { 
                                return ((addr.MediaTypes & TAPIMEDIATYPES.AUDIO) != 0); 
                            }));

                if (comboBox1.Items.Count > 0)
                {
                    comboBox1.SelectedIndex = 0;
                    selectedAddress = (TAddress)comboBox1.SelectedItem;
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString());
            }
        }

        private void tapi_TE_CALLSTATE(object sender, TapiCallStateEventArgs e)
        {
            if (e.State == CALL_STATE.CS_CONNECTED && playbackTerminal != null)
            {
                // Start the playback message..
                playbackTerminal.Start();
            }
            else if (e.State == CALL_STATE.CS_DISCONNECTED)
            {
                // Stop recording when the call terminates.
                if (recordTerminal != null)
                    recordTerminal.Stop();

                recordTerminal = null;
                playbackTerminal = null;
            }
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            // Get newly selected address.
            selectedAddress = (TAddress)comboBox1.SelectedItem;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                selectedAddress.Open(TAPIMEDIATYPES.AUDIO);
            }
            catch (TapiException ex)
            {
                MessageBox.Show(ex.Message);
            }

            currCall = selectedAddress.CreateCall(textBox1.Text, LINEADDRESSTYPES.PhoneNumber, TAPIMEDIATYPES.AUDIO);
            if (currCall != null)
            {
                try
                {
                    currCall.Connect(false);
                }
                catch (TapiException ex)
                {
                    MessageBox.Show(ex.Message);
                }

                // This must be done AFTER call is connected.  Otherwise it will not
                // associate the terminal.  This is a requirement of TAPI3 itself.
                try
                {
                    playbackTerminal = currCall.RequestTerminal(
                          TTerminal.FilePlaybackTerminal,
                          TAPIMEDIATYPES.AUDIO, JulMar.Tapi3.TERMINAL_DIRECTION.TD_CAPTURE);
                    if (playbackTerminal != null)
                    {
                        playbackTerminal.MediaPlayList = new string[] { MESSAGE_PROMPT };
                        currCall.SelectTerminalOnCall(playbackTerminal);
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

            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            SaveFileDialog fd = new SaveFileDialog();
            fd.Title = "Saving file";
            fd.InitialDirectory = Environment.CurrentDirectory + "\\Messages";
            fd.RestoreDirectory = true;
            fd.FileName = "message.wav";
            fd.Filter = "WAV files (*.wav)|*.wav";

            if (fd.ShowDialog() == DialogResult.OK)
            {
                RecordConversation(fd.FileName);
            }
        }

        private void RecordConversation(string fileName)
        {
            // This code only works on XP or better (TAPI 3.1).
            if (currCall != null)
            {
                try
                {
                    recordTerminal = currCall.RequestTerminal(
                        TTerminal.FileRecordingTerminal,
                        TAPIMEDIATYPES.MULTITRACK, TERMINAL_DIRECTION.TD_RENDER);
                    if (recordTerminal != null)
                    {
                        recordTerminal.RecordFileName = fileName;
                        currCall.SelectTerminalOnCall(recordTerminal);
                        recordTerminal.Start();
                    }
                    else
                    {
                        MessageBox.Show("Failed to retrieve terminal.");
                    }
                }
                catch (TapiException ex)
                {
                    MessageBox.Show(ex.Message);
                }
             
            }
          
        }
    }
}