namespace OutgoingSample
{
    partial class OutgoingForm
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
            this.label1 = new System.Windows.Forms.Label();
            this.btnDial = new System.Windows.Forms.Button();
            this.cbDestinationType = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.textDestination = new System.Windows.Forms.TextBox();
            this.btnDisconnect = new System.Windows.Forms.Button();
            this.btnExit = new System.Windows.Forms.Button();
            this.cbAddress = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.tapi = new JulMar.Tapi3.TTapi();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 55);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(126, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Destination address type:";
            // 
            // btnDial
            // 
            this.btnDial.Location = new System.Drawing.Point(236, 23);
            this.btnDial.Name = "btnDial";
            this.btnDial.Size = new System.Drawing.Size(75, 23);
            this.btnDial.TabIndex = 6;
            this.btnDial.Text = "D&ial";
            this.btnDial.UseVisualStyleBackColor = true;
            this.btnDial.Click += new System.EventHandler(this.OnDial);
            // 
            // cbDestinationType
            // 
            this.cbDestinationType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbDestinationType.FormattingEnabled = true;
            this.cbDestinationType.Location = new System.Drawing.Point(6, 71);
            this.cbDestinationType.Name = "cbDestinationType";
            this.cbDestinationType.Size = new System.Drawing.Size(215, 21);
            this.cbDestinationType.TabIndex = 3;
            this.cbDestinationType.SelectedIndexChanged += new System.EventHandler(this.cbDestination_SelectedIndexChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 109);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(103, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Destination address:";
            // 
            // textDestination
            // 
            this.textDestination.Location = new System.Drawing.Point(6, 126);
            this.textDestination.Name = "textDestination";
            this.textDestination.Size = new System.Drawing.Size(215, 20);
            this.textDestination.TabIndex = 5;
            this.textDestination.TextChanged += new System.EventHandler(this.Destination_TextChanged);
            // 
            // btnDisconnect
            // 
            this.btnDisconnect.Enabled = false;
            this.btnDisconnect.Location = new System.Drawing.Point(236, 69);
            this.btnDisconnect.Name = "btnDisconnect";
            this.btnDisconnect.Size = new System.Drawing.Size(75, 23);
            this.btnDisconnect.TabIndex = 7;
            this.btnDisconnect.Text = "&Disconnect";
            this.btnDisconnect.UseVisualStyleBackColor = true;
            this.btnDisconnect.Click += new System.EventHandler(this.OnDisconnect);
            // 
            // btnExit
            // 
            this.btnExit.Location = new System.Drawing.Point(236, 123);
            this.btnExit.Name = "btnExit";
            this.btnExit.Size = new System.Drawing.Size(75, 23);
            this.btnExit.TabIndex = 8;
            this.btnExit.Text = "E&xit";
            this.btnExit.UseVisualStyleBackColor = true;
            this.btnExit.Click += new System.EventHandler(this.OnExit);
            // 
            // cbAddress
            // 
            this.cbAddress.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbAddress.FormattingEnabled = true;
            this.cbAddress.Location = new System.Drawing.Point(6, 23);
            this.cbAddress.Name = "cbAddress";
            this.cbAddress.Size = new System.Drawing.Size(215, 21);
            this.cbAddress.TabIndex = 1;
            this.cbAddress.SelectedIndexChanged += new System.EventHandler(this.cbAddress_SelectedIndexChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(3, 7);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(84, 13);
            this.label3.TabIndex = 0;
            this.label3.Text = "Source address:";
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1});
            this.statusStrip1.Location = new System.Drawing.Point(0, 147);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(324, 22);
            this.statusStrip1.TabIndex = 9;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(309, 17);
            this.toolStripStatusLabel1.Spring = true;
            this.toolStripStatusLabel1.Text = "Ready";
            this.toolStripStatusLabel1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // tapi
            // 
            this.tapi.TE_FILETERMINAL += new System.EventHandler<JulMar.Tapi3.TapiFileTerminalEventArgs>(this.OnFileTerminal);
            this.tapi.TE_CALLNOTIFICATION += new System.EventHandler<JulMar.Tapi3.TapiCallNotificationEventArgs>(this.OnNewCall);
            this.tapi.TE_CALLMEDIA += new System.EventHandler<JulMar.Tapi3.TapiCallMediaEventArgs>(this.OnMediaEvent);
            this.tapi.TE_CALLSTATE += new System.EventHandler<JulMar.Tapi3.TapiCallStateEventArgs>(this.OnCallStateChanged);
            // 
            // OutgoingForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(324, 169);
            this.Controls.Add(this.btnExit);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.cbAddress);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.btnDisconnect);
            this.Controls.Add(this.textDestination);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.cbDestinationType);
            this.Controls.Add(this.btnDial);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.Name = "OutgoingForm";
            this.Text = "Tapi3 Outgoing Call Sample";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.OnClose);
            this.Load += new System.EventHandler(this.OnLoad);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnDial;
        private System.Windows.Forms.ComboBox cbDestinationType;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textDestination;
        private System.Windows.Forms.Button btnDisconnect;
        private System.Windows.Forms.Button btnExit;
        private System.Windows.Forms.ComboBox cbAddress;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private JulMar.Tapi3.TTapi tapi;
    }
}

