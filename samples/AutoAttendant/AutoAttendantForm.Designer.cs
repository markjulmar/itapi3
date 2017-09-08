namespace AnsMachine
{
    partial class AutoAttendantForm
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
            this.textStatus = new System.Windows.Forms.TextBox();
            this.btnExit = new System.Windows.Forms.Button();
            this.tTapi = new JulMar.Tapi3.TTapi();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(40, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Status:";
            // 
            // textStatus
            // 
            this.textStatus.Location = new System.Drawing.Point(6, 25);
            this.textStatus.Name = "textStatus";
            this.textStatus.ReadOnly = true;
            this.textStatus.Size = new System.Drawing.Size(171, 20);
            this.textStatus.TabIndex = 1;
            // 
            // btnExit
            // 
            this.btnExit.Location = new System.Drawing.Point(186, 22);
            this.btnExit.Name = "btnExit";
            this.btnExit.Size = new System.Drawing.Size(75, 23);
            this.btnExit.TabIndex = 2;
            this.btnExit.Text = "E&xit";
            this.btnExit.UseVisualStyleBackColor = true;
            this.btnExit.Click += new System.EventHandler(this.btnExit_Click);
            // 
            // tTapi
            // 
            this.tTapi.TE_FILETERMINAL += new System.EventHandler<JulMar.Tapi3.TapiFileTerminalEventArgs>(this.OnFileTerminal);
            this.tTapi.TE_CALLNOTIFICATION += new System.EventHandler<JulMar.Tapi3.TapiCallNotificationEventArgs>(this.OnNewCall);
            this.tTapi.TE_CALLMEDIA += new System.EventHandler<JulMar.Tapi3.TapiCallMediaEventArgs>(this.OnCallMedia);
            this.tTapi.TE_CALLSTATE += new System.EventHandler<JulMar.Tapi3.TapiCallStateEventArgs>(this.OnCallState);
            // 
            // AutoAttendantForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(273, 65);
            this.Controls.Add(this.btnExit);
            this.Controls.Add(this.textStatus);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.Name = "AutoAttendantForm";
            this.Text = "Auto Attendant";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form_Closing);
            this.Load += new System.EventHandler(this.Form_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textStatus;
        private System.Windows.Forms.Button btnExit;
        private JulMar.Tapi3.TTapi tTapi;
    }
}

