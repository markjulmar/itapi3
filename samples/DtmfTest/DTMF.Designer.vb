<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> Partial Class frmDTMF
#Region "Windows Form Designer generated code "
	<System.Diagnostics.DebuggerNonUserCode()> Public Sub New()
		MyBase.New()
		'This call is required by the Windows Form Designer.
		InitializeComponent()
	End Sub
	'Form overrides dispose to clean up the component list.
	<System.Diagnostics.DebuggerNonUserCode()> Protected Overloads Overrides Sub Dispose(ByVal Disposing As Boolean)
		If Disposing Then
			If Not components Is Nothing Then
				components.Dispose()
			End If
		End If
		MyBase.Dispose(Disposing)
	End Sub
	'Required by the Windows Form Designer
	Private components As System.ComponentModel.IContainer
	Public ToolTip1 As System.Windows.Forms.ToolTip
	Public WithEvents cbSelectTerminals As System.Windows.Forms.CheckBox
	Public WithEvents pbRelease As System.Windows.Forms.Button
	Public WithEvents cmbAddresses As System.Windows.Forms.ComboBox
	Public WithEvents pbStopDetect As System.Windows.Forms.Button
	Public WithEvents pbStartDetect As System.Windows.Forms.Button
	Public WithEvents Frame3 As System.Windows.Forms.GroupBox
	Public WithEvents txtStatus As System.Windows.Forms.TextBox
	Public WithEvents cbModePulse As System.Windows.Forms.CheckBox
	Public WithEvents cbModeDTMFEND As System.Windows.Forms.CheckBox
	Public WithEvents cbModeDTMF As System.Windows.Forms.CheckBox
	Public WithEvents pbGenerate As System.Windows.Forms.Button
	Public WithEvents txtDigitsToGenerate As System.Windows.Forms.TextBox
	Public WithEvents txtDestAddress As System.Windows.Forms.TextBox
	Public WithEvents pbDial As System.Windows.Forms.Button
	Public WithEvents pbDisconnect As System.Windows.Forms.Button
	Public WithEvents Frame1 As System.Windows.Forms.GroupBox
	Public WithEvents Label1 As System.Windows.Forms.Label
	Public WithEvents Frame2 As System.Windows.Forms.GroupBox
	Public WithEvents Line2 As System.Windows.Forms.Label
	Public WithEvents Label3 As System.Windows.Forms.Label
	Public WithEvents Line1 As System.Windows.Forms.Label
	Public WithEvents Label2 As System.Windows.Forms.Label
	Public WithEvents lblStatusTitle As System.Windows.Forms.Label
	'NOTE: The following procedure is required by the Windows Form Designer
	'It can be modified using the Windows Form Designer.
	'Do not modify it using the code editor.
	<System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.cbSelectTerminals = New System.Windows.Forms.CheckBox
        Me.pbRelease = New System.Windows.Forms.Button
        Me.cmbAddresses = New System.Windows.Forms.ComboBox
        Me.Frame3 = New System.Windows.Forms.GroupBox
        Me.pbStopDetect = New System.Windows.Forms.Button
        Me.pbStartDetect = New System.Windows.Forms.Button
        Me.txtStatus = New System.Windows.Forms.TextBox
        Me.cbModePulse = New System.Windows.Forms.CheckBox
        Me.cbModeDTMFEND = New System.Windows.Forms.CheckBox
        Me.cbModeDTMF = New System.Windows.Forms.CheckBox
        Me.pbGenerate = New System.Windows.Forms.Button
        Me.txtDigitsToGenerate = New System.Windows.Forms.TextBox
        Me.txtDestAddress = New System.Windows.Forms.TextBox
        Me.pbDial = New System.Windows.Forms.Button
        Me.pbDisconnect = New System.Windows.Forms.Button
        Me.Frame1 = New System.Windows.Forms.GroupBox
        Me.Frame2 = New System.Windows.Forms.GroupBox
        Me.Label1 = New System.Windows.Forms.Label
        Me.Line2 = New System.Windows.Forms.Label
        Me.Label3 = New System.Windows.Forms.Label
        Me.Line1 = New System.Windows.Forms.Label
        Me.Label2 = New System.Windows.Forms.Label
        Me.lblStatusTitle = New System.Windows.Forms.Label
        Me.mobjTapi = New JulMar.Tapi3.TTapi
        Me.cmbAddressType = New System.Windows.Forms.ComboBox
        Me.Label4 = New System.Windows.Forms.Label
        Me.Frame3.SuspendLayout()
        Me.Frame2.SuspendLayout()
        Me.SuspendLayout()
        '
        'cbSelectTerminals
        '
        Me.cbSelectTerminals.BackColor = System.Drawing.SystemColors.Control
        Me.cbSelectTerminals.Cursor = System.Windows.Forms.Cursors.Default
        Me.cbSelectTerminals.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cbSelectTerminals.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cbSelectTerminals.Location = New System.Drawing.Point(120, 98)
        Me.cbSelectTerminals.Name = "cbSelectTerminals"
        Me.cbSelectTerminals.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cbSelectTerminals.Size = New System.Drawing.Size(153, 21)
        Me.cbSelectTerminals.TabIndex = 20
        Me.cbSelectTerminals.Text = "Select Audio Terminals"
        Me.cbSelectTerminals.UseVisualStyleBackColor = False
        '
        'pbRelease
        '
        Me.pbRelease.BackColor = System.Drawing.SystemColors.Control
        Me.pbRelease.Cursor = System.Windows.Forms.Cursors.Default
        Me.pbRelease.Enabled = False
        Me.pbRelease.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.pbRelease.ForeColor = System.Drawing.SystemColors.ControlText
        Me.pbRelease.Location = New System.Drawing.Point(304, 80)
        Me.pbRelease.Name = "pbRelease"
        Me.pbRelease.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.pbRelease.Size = New System.Drawing.Size(161, 25)
        Me.pbRelease.TabIndex = 19
        Me.pbRelease.Text = "ReleaseCall"
        Me.pbRelease.UseVisualStyleBackColor = False
        '
        'cmbAddresses
        '
        Me.cmbAddresses.BackColor = System.Drawing.SystemColors.Window
        Me.cmbAddresses.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmbAddresses.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmbAddresses.ForeColor = System.Drawing.SystemColors.WindowText
        Me.cmbAddresses.Location = New System.Drawing.Point(120, 16)
        Me.cmbAddresses.Name = "cmbAddresses"
        Me.cmbAddresses.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmbAddresses.Size = New System.Drawing.Size(177, 22)
        Me.cmbAddresses.TabIndex = 17
        '
        'Frame3
        '
        Me.Frame3.BackColor = System.Drawing.SystemColors.Control
        Me.Frame3.Controls.Add(Me.pbStopDetect)
        Me.Frame3.Controls.Add(Me.pbStartDetect)
        Me.Frame3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Frame3.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Frame3.Location = New System.Drawing.Point(328, 146)
        Me.Frame3.Name = "Frame3"
        Me.Frame3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Frame3.Size = New System.Drawing.Size(177, 113)
        Me.Frame3.TabIndex = 13
        Me.Frame3.TabStop = False
        Me.Frame3.Text = "Digit Detection"
        '
        'pbStopDetect
        '
        Me.pbStopDetect.BackColor = System.Drawing.SystemColors.Control
        Me.pbStopDetect.Cursor = System.Windows.Forms.Cursors.Default
        Me.pbStopDetect.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.pbStopDetect.ForeColor = System.Drawing.SystemColors.ControlText
        Me.pbStopDetect.Location = New System.Drawing.Point(40, 64)
        Me.pbStopDetect.Name = "pbStopDetect"
        Me.pbStopDetect.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.pbStopDetect.Size = New System.Drawing.Size(97, 25)
        Me.pbStopDetect.TabIndex = 15
        Me.pbStopDetect.Text = "Stop Detect"
        Me.pbStopDetect.UseVisualStyleBackColor = False
        '
        'pbStartDetect
        '
        Me.pbStartDetect.BackColor = System.Drawing.SystemColors.Control
        Me.pbStartDetect.Cursor = System.Windows.Forms.Cursors.Default
        Me.pbStartDetect.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.pbStartDetect.ForeColor = System.Drawing.SystemColors.ControlText
        Me.pbStartDetect.Location = New System.Drawing.Point(40, 24)
        Me.pbStartDetect.Name = "pbStartDetect"
        Me.pbStartDetect.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.pbStartDetect.Size = New System.Drawing.Size(97, 25)
        Me.pbStartDetect.TabIndex = 14
        Me.pbStartDetect.Text = "Start Detect"
        Me.pbStartDetect.UseVisualStyleBackColor = False
        '
        'txtStatus
        '
        Me.txtStatus.AcceptsReturn = True
        Me.txtStatus.BackColor = System.Drawing.SystemColors.Window
        Me.txtStatus.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtStatus.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtStatus.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtStatus.Location = New System.Drawing.Point(15, 298)
        Me.txtStatus.MaxLength = 0
        Me.txtStatus.Multiline = True
        Me.txtStatus.Name = "txtStatus"
        Me.txtStatus.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtStatus.ScrollBars = System.Windows.Forms.ScrollBars.Both
        Me.txtStatus.Size = New System.Drawing.Size(505, 145)
        Me.txtStatus.TabIndex = 3
        Me.txtStatus.WordWrap = False
        '
        'cbModePulse
        '
        Me.cbModePulse.BackColor = System.Drawing.SystemColors.Control
        Me.cbModePulse.Cursor = System.Windows.Forms.Cursors.Default
        Me.cbModePulse.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cbModePulse.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cbModePulse.Location = New System.Drawing.Point(35, 210)
        Me.cbModePulse.Name = "cbModePulse"
        Me.cbModePulse.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cbModePulse.Size = New System.Drawing.Size(73, 17)
        Me.cbModePulse.TabIndex = 6
        Me.cbModePulse.Text = "Pulse"
        Me.cbModePulse.UseVisualStyleBackColor = False
        '
        'cbModeDTMFEND
        '
        Me.cbModeDTMFEND.BackColor = System.Drawing.SystemColors.Control
        Me.cbModeDTMFEND.Cursor = System.Windows.Forms.Cursors.Default
        Me.cbModeDTMFEND.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cbModeDTMFEND.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cbModeDTMFEND.Location = New System.Drawing.Point(35, 186)
        Me.cbModeDTMFEND.Name = "cbModeDTMFEND"
        Me.cbModeDTMFEND.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cbModeDTMFEND.Size = New System.Drawing.Size(73, 17)
        Me.cbModeDTMFEND.TabIndex = 5
        Me.cbModeDTMFEND.Text = "DTMFEND"
        Me.cbModeDTMFEND.UseVisualStyleBackColor = False
        '
        'cbModeDTMF
        '
        Me.cbModeDTMF.BackColor = System.Drawing.SystemColors.Control
        Me.cbModeDTMF.Checked = True
        Me.cbModeDTMF.CheckState = System.Windows.Forms.CheckState.Checked
        Me.cbModeDTMF.Cursor = System.Windows.Forms.Cursors.Default
        Me.cbModeDTMF.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cbModeDTMF.ForeColor = System.Drawing.SystemColors.ControlText
        Me.cbModeDTMF.Location = New System.Drawing.Point(35, 162)
        Me.cbModeDTMF.Name = "cbModeDTMF"
        Me.cbModeDTMF.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cbModeDTMF.Size = New System.Drawing.Size(73, 17)
        Me.cbModeDTMF.TabIndex = 4
        Me.cbModeDTMF.Text = "DTMF"
        Me.cbModeDTMF.UseVisualStyleBackColor = False
        '
        'pbGenerate
        '
        Me.pbGenerate.BackColor = System.Drawing.SystemColors.Control
        Me.pbGenerate.Cursor = System.Windows.Forms.Cursors.Default
        Me.pbGenerate.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.pbGenerate.ForeColor = System.Drawing.SystemColors.ControlText
        Me.pbGenerate.Location = New System.Drawing.Point(163, 218)
        Me.pbGenerate.Name = "pbGenerate"
        Me.pbGenerate.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.pbGenerate.Size = New System.Drawing.Size(113, 25)
        Me.pbGenerate.TabIndex = 8
        Me.pbGenerate.Text = "Generate"
        Me.pbGenerate.UseVisualStyleBackColor = False
        '
        'txtDigitsToGenerate
        '
        Me.txtDigitsToGenerate.AcceptsReturn = True
        Me.txtDigitsToGenerate.BackColor = System.Drawing.SystemColors.Window
        Me.txtDigitsToGenerate.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtDigitsToGenerate.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtDigitsToGenerate.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtDigitsToGenerate.Location = New System.Drawing.Point(155, 186)
        Me.txtDigitsToGenerate.MaxLength = 20
        Me.txtDigitsToGenerate.Name = "txtDigitsToGenerate"
        Me.txtDigitsToGenerate.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtDigitsToGenerate.Size = New System.Drawing.Size(137, 20)
        Me.txtDigitsToGenerate.TabIndex = 7
        Me.txtDigitsToGenerate.Text = "0123456789ABCD*#"
        '
        'txtDestAddress
        '
        Me.txtDestAddress.AcceptsReturn = True
        Me.txtDestAddress.BackColor = System.Drawing.SystemColors.Window
        Me.txtDestAddress.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.txtDestAddress.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.txtDestAddress.ForeColor = System.Drawing.SystemColors.WindowText
        Me.txtDestAddress.Location = New System.Drawing.Point(120, 44)
        Me.txtDestAddress.MaxLength = 20
        Me.txtDestAddress.Name = "txtDestAddress"
        Me.txtDestAddress.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.txtDestAddress.Size = New System.Drawing.Size(177, 20)
        Me.txtDestAddress.TabIndex = 0
        Me.txtDestAddress.Text = "24311"
        '
        'pbDial
        '
        Me.pbDial.BackColor = System.Drawing.SystemColors.Control
        Me.pbDial.Cursor = System.Windows.Forms.Cursors.Default
        Me.pbDial.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.pbDial.ForeColor = System.Drawing.SystemColors.ControlText
        Me.pbDial.Location = New System.Drawing.Point(304, 16)
        Me.pbDial.Name = "pbDial"
        Me.pbDial.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.pbDial.Size = New System.Drawing.Size(161, 25)
        Me.pbDial.TabIndex = 1
        Me.pbDial.Text = "Dial"
        Me.pbDial.UseVisualStyleBackColor = False
        '
        'pbDisconnect
        '
        Me.pbDisconnect.BackColor = System.Drawing.SystemColors.Control
        Me.pbDisconnect.Cursor = System.Windows.Forms.Cursors.Default
        Me.pbDisconnect.Enabled = False
        Me.pbDisconnect.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.pbDisconnect.ForeColor = System.Drawing.SystemColors.ControlText
        Me.pbDisconnect.Location = New System.Drawing.Point(304, 48)
        Me.pbDisconnect.Name = "pbDisconnect"
        Me.pbDisconnect.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.pbDisconnect.Size = New System.Drawing.Size(161, 25)
        Me.pbDisconnect.TabIndex = 2
        Me.pbDisconnect.Text = "Disconnect"
        Me.pbDisconnect.UseVisualStyleBackColor = False
        '
        'Frame1
        '
        Me.Frame1.BackColor = System.Drawing.SystemColors.Control
        Me.Frame1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Frame1.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Frame1.Location = New System.Drawing.Point(27, 146)
        Me.Frame1.Name = "Frame1"
        Me.Frame1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Frame1.Size = New System.Drawing.Size(89, 89)
        Me.Frame1.TabIndex = 11
        Me.Frame1.TabStop = False
        Me.Frame1.Text = "Digit Mode"
        '
        'Frame2
        '
        Me.Frame2.BackColor = System.Drawing.SystemColors.Control
        Me.Frame2.Controls.Add(Me.Label1)
        Me.Frame2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Frame2.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Frame2.Location = New System.Drawing.Point(139, 146)
        Me.Frame2.Name = "Frame2"
        Me.Frame2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Frame2.Size = New System.Drawing.Size(169, 113)
        Me.Frame2.TabIndex = 12
        Me.Frame2.TabStop = False
        Me.Frame2.Text = "Digit Generation"
        '
        'Label1
        '
        Me.Label1.BackColor = System.Drawing.SystemColors.Control
        Me.Label1.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label1.Location = New System.Drawing.Point(16, 24)
        Me.Label1.Name = "Label1"
        Me.Label1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label1.Size = New System.Drawing.Size(137, 17)
        Me.Label1.TabIndex = 16
        Me.Label1.Text = "Digits to generate:"
        '
        'Line2
        '
        Me.Line2.BackColor = System.Drawing.SystemColors.WindowText
        Me.Line2.Location = New System.Drawing.Point(16, 274)
        Me.Line2.Name = "Line2"
        Me.Line2.Size = New System.Drawing.Size(496, 1)
        Me.Line2.TabIndex = 21
        '
        'Label3
        '
        Me.Label3.BackColor = System.Drawing.SystemColors.Control
        Me.Label3.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label3.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label3.Location = New System.Drawing.Point(8, 19)
        Me.Label3.Name = "Label3"
        Me.Label3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label3.Size = New System.Drawing.Size(108, 19)
        Me.Label3.TabIndex = 18
        Me.Label3.Text = "Origination address:"
        '
        'Line1
        '
        Me.Line1.BackColor = System.Drawing.SystemColors.WindowText
        Me.Line1.Location = New System.Drawing.Point(19, 130)
        Me.Line1.Name = "Line1"
        Me.Line1.Size = New System.Drawing.Size(496, 1)
        Me.Line1.TabIndex = 22
        '
        'Label2
        '
        Me.Label2.BackColor = System.Drawing.SystemColors.Control
        Me.Label2.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label2.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label2.Location = New System.Drawing.Point(8, 47)
        Me.Label2.Name = "Label2"
        Me.Label2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label2.Size = New System.Drawing.Size(108, 16)
        Me.Label2.TabIndex = 10
        Me.Label2.Text = "Destination address:"
        '
        'lblStatusTitle
        '
        Me.lblStatusTitle.BackColor = System.Drawing.SystemColors.Control
        Me.lblStatusTitle.Cursor = System.Windows.Forms.Cursors.Default
        Me.lblStatusTitle.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.lblStatusTitle.ForeColor = System.Drawing.SystemColors.ControlText
        Me.lblStatusTitle.Location = New System.Drawing.Point(16, 282)
        Me.lblStatusTitle.Name = "lblStatusTitle"
        Me.lblStatusTitle.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.lblStatusTitle.Size = New System.Drawing.Size(41, 17)
        Me.lblStatusTitle.TabIndex = 9
        Me.lblStatusTitle.Text = "Status:"
        '
        'mobjTapi
        '
        Me.mobjTapi.AutoDestroyCalls = False
        '
        'cmbAddressType
        '
        Me.cmbAddressType.BackColor = System.Drawing.SystemColors.Window
        Me.cmbAddressType.Cursor = System.Windows.Forms.Cursors.Default
        Me.cmbAddressType.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.cmbAddressType.ForeColor = System.Drawing.SystemColors.WindowText
        Me.cmbAddressType.Location = New System.Drawing.Point(120, 70)
        Me.cmbAddressType.Name = "cmbAddressType"
        Me.cmbAddressType.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.cmbAddressType.Size = New System.Drawing.Size(177, 22)
        Me.cmbAddressType.TabIndex = 23
        '
        'Label4
        '
        Me.Label4.BackColor = System.Drawing.SystemColors.Control
        Me.Label4.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label4.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label4.Location = New System.Drawing.Point(8, 73)
        Me.Label4.Name = "Label4"
        Me.Label4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label4.Size = New System.Drawing.Size(108, 19)
        Me.Label4.TabIndex = 24
        Me.Label4.Text = "Address Type:"
        '
        'frmDTMF
        '
        Me.AcceptButton = Me.pbDial
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 14.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.SystemColors.Control
        Me.ClientSize = New System.Drawing.Size(534, 437)
        Me.Controls.Add(Me.cmbAddressType)
        Me.Controls.Add(Me.Label4)
        Me.Controls.Add(Me.cbSelectTerminals)
        Me.Controls.Add(Me.pbRelease)
        Me.Controls.Add(Me.cmbAddresses)
        Me.Controls.Add(Me.Frame3)
        Me.Controls.Add(Me.txtStatus)
        Me.Controls.Add(Me.cbModePulse)
        Me.Controls.Add(Me.cbModeDTMFEND)
        Me.Controls.Add(Me.cbModeDTMF)
        Me.Controls.Add(Me.pbGenerate)
        Me.Controls.Add(Me.txtDigitsToGenerate)
        Me.Controls.Add(Me.txtDestAddress)
        Me.Controls.Add(Me.pbDial)
        Me.Controls.Add(Me.pbDisconnect)
        Me.Controls.Add(Me.Frame1)
        Me.Controls.Add(Me.Frame2)
        Me.Controls.Add(Me.Line2)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.Line1)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.lblStatusTitle)
        Me.Cursor = System.Windows.Forms.Cursors.Default
        Me.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Location = New System.Drawing.Point(4, 23)
        Me.Name = "frmDTMF"
        Me.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Text = "DTMF demo"
        Me.Frame3.ResumeLayout(False)
        Me.Frame2.ResumeLayout(False)
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents mobjTapi As JulMar.Tapi3.TTapi
    Public WithEvents cmbAddressType As System.Windows.Forms.ComboBox
    Public WithEvents Label4 As System.Windows.Forms.Label
#End Region 
End Class