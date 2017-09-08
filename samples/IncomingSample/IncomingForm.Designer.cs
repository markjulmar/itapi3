namespace IncomingSample
{
    partial class IncomingForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.lbCalls = new System.Windows.Forms.ListBox();
            this.btnAnswer = new System.Windows.Forms.Button();
            this.btnDisconnect = new System.Windows.Forms.Button();
            this.localVidPlaceholder = new System.Windows.Forms.Panel();
            this.remoteVidPlaceholder = new System.Windows.Forms.Panel();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this._tapiMgr = new JulMar.Tapi3.TTapi();
            this.SuspendLayout();
            // 
            // lbCalls
            // 
            this.lbCalls.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.lbCalls.FormattingEnabled = true;
            this.lbCalls.IntegralHeight = false;
            this.lbCalls.Location = new System.Drawing.Point(12, 12);
            this.lbCalls.Name = "lbCalls";
            this.lbCalls.Size = new System.Drawing.Size(162, 138);
            this.lbCalls.TabIndex = 0;
            this.lbCalls.SelectedIndexChanged += new System.EventHandler(this.OnSelectedCallChange);
            // 
            // btnAnswer
            // 
            this.btnAnswer.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.btnAnswer.Enabled = false;
            this.btnAnswer.Location = new System.Drawing.Point(14, 156);
            this.btnAnswer.Name = "btnAnswer";
            this.btnAnswer.Size = new System.Drawing.Size(74, 23);
            this.btnAnswer.TabIndex = 1;
            this.btnAnswer.Text = "Answer";
            this.btnAnswer.UseVisualStyleBackColor = true;
            this.btnAnswer.Click += new System.EventHandler(this.OnAnswerClicked);
            // 
            // btnDisconnect
            // 
            this.btnDisconnect.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.btnDisconnect.Enabled = false;
            this.btnDisconnect.Location = new System.Drawing.Point(98, 156);
            this.btnDisconnect.Name = "btnDisconnect";
            this.btnDisconnect.Size = new System.Drawing.Size(74, 23);
            this.btnDisconnect.TabIndex = 2;
            this.btnDisconnect.Text = "Disconnect";
            this.btnDisconnect.UseVisualStyleBackColor = true;
            this.btnDisconnect.Click += new System.EventHandler(this.OnDisconnectClicked);
            // 
            // localVidPlaceholder
            // 
            this.localVidPlaceholder.Location = new System.Drawing.Point(180, 12);
            this.localVidPlaceholder.Name = "localVidPlaceholder";
            this.localVidPlaceholder.Size = new System.Drawing.Size(169, 156);
            this.localVidPlaceholder.TabIndex = 3;
            // 
            // remoteVidPlaceholder
            // 
            this.remoteVidPlaceholder.Location = new System.Drawing.Point(355, 12);
            this.remoteVidPlaceholder.Name = "remoteVidPlaceholder";
            this.remoteVidPlaceholder.Size = new System.Drawing.Size(169, 156);
            this.remoteVidPlaceholder.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.Color.Blue;
            this.label1.Location = new System.Drawing.Point(226, 171);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(63, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "Local Video";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.ForeColor = System.Drawing.Color.Blue;
            this.label2.Location = new System.Drawing.Point(403, 171);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(74, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "Remote Video";
            // 
            // _tapiMgr
            // 
            this._tapiMgr.TE_CALLNOTIFICATION += new System.EventHandler<JulMar.Tapi3.TapiCallNotificationEventArgs>(this.OnNewCall);
            this._tapiMgr.TE_CALLMEDIA += new System.EventHandler<JulMar.Tapi3.TapiCallMediaEventArgs>(this.OnMediaChange);
            this._tapiMgr.TE_CALLSTATE += new System.EventHandler<JulMar.Tapi3.TapiCallStateEventArgs>(this.OnCallStateChange);
            // 
            // IncomingForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(532, 197);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.remoteVidPlaceholder);
            this.Controls.Add(this.localVidPlaceholder);
            this.Controls.Add(this.btnDisconnect);
            this.Controls.Add(this.btnAnswer);
            this.Controls.Add(this.lbCalls);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "IncomingForm";
            this.Text = "Tapi3 Incoming Sample";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.IncomingForm_FormClosed);
            this.Load += new System.EventHandler(this.IncomingForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox lbCalls;
        private System.Windows.Forms.Button btnAnswer;
        private System.Windows.Forms.Button btnDisconnect;
        private System.Windows.Forms.Panel localVidPlaceholder;
        private System.Windows.Forms.Panel remoteVidPlaceholder;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private JulMar.Tapi3.TTapi _tapiMgr;
    }
}

