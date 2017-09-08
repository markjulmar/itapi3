Option Strict Off
Option Explicit On
Friend Class frmDTMF
	Inherits System.Windows.Forms.Form
	'--------------------------------------------------------------------------
	'
	'  Copyright (C) 1997-1999 Microsoft Corporation. All rights reserved.
    '
    '  Adapted by Matthias Moetje (www.terasens.com) for JulMar.ITapi3 library
    '
    '--------------------------------------------------------------------------
	'
	' DTMF = makes Tapi3 outgoing asynchronous call, on which DTMF tones can be generated.
	'
	' This app needs a voice modem to be in the system, because
	' this can generate/detect DTMF tones.
	' Alternatively, the H323 (IP telephony) line exposed by the H323 provider
	' offers DTMF functionality as well.
	' It allows the user to make an outgoing call.
	' On the call, it selects the default terminals for audio+capture and audio+render
	' if it finds any such terminals, and also if the user choses to select them.
	' On the call, it allows the user to generate/detect digits - the user can
	' do that by pressing the corresponding buttons from the form.
	'
	
	
	'
	'user defined types
	'
	
	Enum TestError
		'TErr_NotInitialized = 0
		TErr_Ok = 1
		TErr_Fail = 2
	End Enum
	
	'
	'Constants defined by tapi.h (tapi2.x), tapi3err.h (tapi3.0) or winerror.h
	'for error codes:
	'
	'Note: all tapi constants are defined as VB constants in the file "tapi.txt", which
	'you can find in the subdirectory ..\include that comes with the TAPI3 VB samples.
	'If you use VB6.0, you can open the file tapi.txt using VB's tool "API Text Viewer";
	'then you can use this tool to copy/paste constants in your code.
	'
	
	'tapi3err.h constants
	Const LINEGENERATETERM_DONE As Short = &H1s
	Const LINEGENERATETERM_CANCEL As Short = &H2s
	
	'other constants
	Const NO_ERROR As Short = 0 'Err.Number = 0 when there is no error

	'
	'global variables
	'
	
	'TAPI objects
	Private mbInitialized As Boolean

	'current address + related info
    Private mobjOrigAddress As JulMar.Tapi3.TAddress

	Private mnPreviousAddressIndex As Integer
    Private mvarArrAudioTerminals As Object

    'current call
    Private mobjCall As JulMar.Tapi3.TCall

	
	Private Sub frmDTMF_Load(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Load


		'initialize UI
		pbDial.Enabled = True
		pbDisconnect.Enabled = False
		pbRelease.Enabled = False
		
		pbGenerate.Enabled = False
		pbStartDetect.Enabled = False
		pbStopDetect.Enabled = False
		
		'initialize Tapi
		InitializeTapiObjects()
		
		'populate combo with all addresses , regardless
		'of their possibility to support the Digit Terminal class
        Call PopulateAddressesCombo(mobjTapi, False)

        'Populate Address Type Combo
        Dim i As Long = cmbAddressType.Items.Add("Phone Number")
        VB6.SetItemData(cmbAddressType, i, JulMar.Tapi3.LINEADDRESSTYPES.PhoneNumber)
        i = cmbAddressType.Items.Add("Domain Name")
        VB6.SetItemData(cmbAddressType, i, JulMar.Tapi3.LINEADDRESSTYPES.DomainName)
        i = cmbAddressType.Items.Add("EMail Address")
        VB6.SetItemData(cmbAddressType, i, JulMar.Tapi3.LINEADDRESSTYPES.EmailName)
        i = cmbAddressType.Items.Add("IP Address")
        VB6.SetItemData(cmbAddressType, i, JulMar.Tapi3.LINEADDRESSTYPES.IPAddress)

        cmbAddressType.SelectedIndex = 0


	End Sub
	
	Private Sub frmDTMF_FormClosed(ByVal eventSender As System.Object, ByVal eventArgs As System.Windows.Forms.FormClosedEventArgs) Handles Me.FormClosed
		'release all member data "object" variables
		Call ReleaseAllMembers()
		
		'release combo with addresses
		Call DepopulateAddressesCombo()
	End Sub
	
	'
	'This function is called only once, when the form is loaded.
	'
	'This function populates the combobox with the names of the addresses,
	'and memorize also in the "data" field the index of each address
	'that corresponds to the collection of addresses from objTapi.
	'Then it selects the 1st item in the combo.
	'
	'If bMustSupportDTMF is set on True, only addresses that have
	'the DTMF functionality are put in combo.
	'
	'Note: we use On Erorr Resume Next, because we want to add as many items as possible
	'
	Sub PopulateAddressesCombo(ByRef objTapi As JulMar.Tapi3.TTapi, ByRef bMustSupportDTMF As Boolean)
        On Error Resume Next 'this will catch errors

        Dim nResult As Integer
        Dim nIterator, nCount As Integer
        Dim collobjAddresses() As JulMar.Tapi3.TAddress
        Dim objCrtAddress As JulMar.Tapi3.TAddress

        'don't need to clean combo of previous contents,
        'because this function is called only once
        'cmbAddresses.Clear

        collobjAddresses = objTapi.Addresses
        nResult = PrintT3Result("PopulateAddressesCombo: objTapi.Addresses")

        If nResult = NO_ERROR Then
            'populate combobox with names of all addresses from collobjAddresses
            'attach to each combo item the index of the corresponding address
            nCount = 0
            nCount = collobjAddresses.Length

            For nIterator = 0 To nCount - 1

                objCrtAddress = collobjAddresses(nIterator)

                nResult = PrintT3Result("PopulateAddressesCombo: enumerate addresses")

                If nResult = NO_ERROR Then

                    If (bMustSupportDTMF = False Or bMustSupportDTMF And SupportDTMF(objCrtAddress)) Then

                        Dim NewIndex As Integer = cmbAddresses.Items.Add((objCrtAddress.AddressName))

                        nResult = PrintT3Result("PopulateAddressesCombo: adding addresses in combo")

                        If nResult = NO_ERROR Then
                            VB6.SetItemData(cmbAddresses, NewIndex, nIterator)
                        End If

                    End If
                End If

            Next nIterator
        End If


        ''set selection on 1st item
        'If cmbAddresses.Items.Count > 0 Then
        '    cmbAddresses.SelectedIndex = 0
        '    'This automatically called cmbAddresses_Click
        'End If

    End Sub
	
	Sub DepopulateAddressesCombo()
		cmbAddresses.Items.Clear()
	End Sub
	
    Private Sub cmbAddresses_TextChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmbAddresses.TextChanged
        Call ChangeAddress()
    End Sub
	
    Private Sub cmbAddresses_SelectedIndexChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cmbAddresses.SelectedIndexChanged
        Call ChangeAddress()
    End Sub
	
	Private Sub ChangeAddress()
		On Error Resume Next 'this will catch errors
		
		Dim nResult As Integer
		Dim nOrigAddressIndex As Integer
		
		'pick up the collection of Address objects
        Dim objCollAddresses() As JulMar.Tapi3.TAddress

		
        objCollAddresses = mobjTapi.Addresses
		nResult = PrintT3Result("ChangeAddress: mobjTapi.Addresses")
		If nResult <> NO_ERROR Then
			Call MsgBox("Fatal error: can't get TAPI addresses, exit program", MsgBoxStyle.Critical)
			Stop 'fatal error
		End If
		
		'find index of address selected by the user
		nOrigAddressIndex = FindOriginationAddressIndex()
		
		'
		'pick up the new address - update all related global variables
		'
		
		If mnPreviousAddressIndex <> nOrigAddressIndex Then
			'If a new address was selected, release the previous one
			'and save a "pointer" to the new one, plus related info
			'If the same address was selected, don't release/save it again,
			'just keep the previous one + its related info.
			
			'
			'clean up previous info
			'
			
            'release old terminals
			Call ReleaseAudioTerminals(mvarArrAudioTerminals)
			
			'wipe out other info
			mnPreviousAddressIndex = 0
			
			'
			'save new info
			'
			
			'validate new index
            If nOrigAddressIndex >= objCollAddresses.GetLowerBound(0) And nOrigAddressIndex <= objCollAddresses.GetUpperBound(0) Then

                'save new address
                mobjOrigAddress = objCollAddresses(nOrigAddressIndex)

                'save also the new index
                mnPreviousAddressIndex = nOrigAddressIndex

                'create new terminals
                Call GetAudioTerminals(mobjOrigAddress, mvarArrAudioTerminals)

            End If
			
		End If
		
		'release objects that are not needed anymore
		'(this decrements the reference count)
    End Sub
	
    Function SupportDTMF(ByRef objAddress As JulMar.Tapi3.TAddress) As Boolean
        On Error Resume Next 'this will catch errors

        Dim nResult, nResult1 As Integer

        Dim lGenerateDigitSupport, lMonitorDigitSupport As Integer

        'prepare return value
        SupportDTMF = False

        nResult = PrintT3Result("SupportDTMF: objAddress->Query (ITAddressCapabilities)")

        If nResult = NO_ERROR Then

            lGenerateDigitSupport = objAddress.AddressCapability(JulMar.Tapi3.ADDRESS_CAPABILITY.AC_GENERATEDIGITSUPPORT)
            nResult = PrintT3Result("SupportDTMF: AddressCapability(AC_GENERATEDIGITSUPPORT)")
            nResult1 = nResult
            lMonitorDigitSupport = objAddress.AddressCapability(JulMar.Tapi3.ADDRESS_CAPABILITY.AC_MONITORDIGITSUPPORT)
            nResult = PrintT3Result("SupportDTMF: AddressCapability(AC_MONITORDIGITSUPPORT)")

            If nResult = NO_ERROR And nResult1 = NO_ERROR Then

                If lGenerateDigitSupport <> 0 And lMonitorDigitSupport <> 0 Then
                    SupportDTMF = True
                End If

            End If

        End If


    End Function
	
    Private Sub PrintCallState(ByRef State As JulMar.Tapi3.CALL_STATE)
        Dim strMsg As String

        Select Case State
            Case JulMar.Tapi3.CALL_STATE.CS_CONNECTED
                txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
                txtStatus.Text = txtStatus.Text & "call state: CS_CONNECTED"
            Case JulMar.Tapi3.CALL_STATE.CS_DISCONNECTED
                strMsg = "call state: CS_DISCONNECTED" & Chr(13) & Chr(10)
                strMsg = strMsg & "Call was disconnected. "
                strMsg = strMsg & "Now you should Release it. "
                strMsg = strMsg & "Then you can press Dial again or just quit."
                txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
                txtStatus.Text = txtStatus.Text & strMsg
            Case JulMar.Tapi3.CALL_STATE.CS_HOLD
                txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
                txtStatus.Text = txtStatus.Text & "call state: CS_HOLD"
            Case JulMar.Tapi3.CALL_STATE.CS_IDLE
                txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
                txtStatus.Text = txtStatus.Text & "call state: CS_IDLE"
            Case JulMar.Tapi3.CALL_STATE.CS_INPROGRESS
                txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
                txtStatus.Text = txtStatus.Text & "call state: CS_INPROGRESS"
            Case JulMar.Tapi3.CALL_STATE.CS_OFFERING
                txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
                txtStatus.Text = txtStatus.Text & "call state: CS_OFFERING"
            Case JulMar.Tapi3.CALL_STATE.CS_QUEUED
                txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
                txtStatus.Text = txtStatus.Text & "call state: CS_QUEUED"
            Case Else
                txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
                txtStatus.Text = txtStatus.Text & "call state: unknown!!"
        End Select

        txtStatus.SelectionStart = Len(txtStatus.Text)
        txtStatus.SelectionLength = 0

    End Sub
	

    Private Sub pbDial_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles pbDial.Click
        On Error Resume Next 'this will catch errors

        Dim nResult As Integer
        Dim nOrigAddressIndex As Integer
        Dim strDestAddress As String
        Dim MyError As Integer

        'second call not supported by this app
        If Not (mobjCall Is Nothing) Then
            txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
            txtStatus.Text = txtStatus.Text & "Cannot connect new call. Wait for the previous one to be disconnected."

            txtStatus.SelectionStart = Len(txtStatus.Text)
            txtStatus.SelectionLength = 0

            Exit Sub
        End If

        'check if user typed input data
        strDestAddress = txtDestAddress.Text
        If strDestAddress = "" Then
            txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
            txtStatus.Text = txtStatus.Text & "Enter destination addres!"

            txtStatus.SelectionStart = Len(txtStatus.Text)
            txtStatus.SelectionLength = 0

            Exit Sub
        End If

        If mobjOrigAddress Is Nothing Then
            txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
            txtStatus.Text = txtStatus.Text & "Select origination address!"

            txtStatus.SelectionStart = Len(txtStatus.Text)
            txtStatus.SelectionLength = 0

            Exit Sub
        End If

        '
        'create the call
        '
        Dim iAddrType As Integer = GetAddressType(mobjOrigAddress)
        If iAddrType = 0 Then Exit Sub

        mobjCall = mobjOrigAddress.CreateCall(strDestAddress, iAddrType, JulMar.Tapi3.TAPIMEDIATYPES.AUDIO)

        nResult = PrintT3Result("pbDial_Click: mobjOrigAddress.CreateCall")
        If nResult <> NO_ERROR Then Exit Sub

        '
        'select on the call the Terminals (ignore returned error code)
        '

        If cbSelectTerminals.CheckState = System.Windows.Forms.CheckState.Checked Then
            Call SelectTerminalsOnStreams(mobjCall, mvarArrAudioTerminals)
        End If

        '
        'Connect the call; False means that the call is made asynchronously.
        'The call to Connect will return immediately, before the call
        'gets to "connected" state; events will fire each time the
        'state of the call changes (to "connected", "disconnected"),
        'meanwhile the application can go on.
        '
        On Error Resume Next
        mobjCall.Connect((False))
        If Err.Number <> 0 Then
            txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
            txtStatus.Text = txtStatus.Text & "Connect failed."

            txtStatus.SelectionStart = Len(txtStatus.Text)
            txtStatus.SelectionLength = 0

            Err.Clear()

        Else
            'update UI
            pbDial.Enabled = False
            pbDisconnect.Enabled = True
            pbRelease.Enabled = False

            pbGenerate.Enabled = True
            pbStartDetect.Enabled = True
            pbStopDetect.Enabled = True

        End If

    End Sub

    Private Sub pbDisconnect_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles pbDisconnect.Click

        Dim nResult As Integer

        If mobjCall Is Nothing Then
            txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
            txtStatus.Text = txtStatus.Text & "There is no call to be disconnected."

            txtStatus.SelectionStart = Len(txtStatus.Text)
            txtStatus.SelectionLength = 0

            Exit Sub
        End If

        mobjCall.Disconnect((JulMar.Tapi3.DISCONNECT_CODE.DC_NORMAL))
        nResult = PrintT3Result("pbDisconnect_Click: mobjCall.Disconnect")
        If nResult <> NO_ERROR Then Exit Sub

    End Sub

    Private Sub pbRelease_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles pbRelease.Click

        'release call
        If mobjCall Is Nothing Then
            txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
            txtStatus.Text = txtStatus.Text & "There is no call to be released."

            txtStatus.SelectionStart = Len(txtStatus.Text)
            txtStatus.SelectionLength = 0

            Exit Sub
        End If

        'Explicitly release the underlying COM call object
        mobjCall.Dispose()
        mobjCall = Nothing

        'update UI

        pbDial.Enabled = True
        pbDisconnect.Enabled = False
        pbRelease.Enabled = False

        pbGenerate.Enabled = False
        pbStartDetect.Enabled = False
        pbStopDetect.Enabled = False

    End Sub

    '
    'This function inspects the given address to see what address types
    'it supports, and then returns the address type if it is supported

    Private Function GetAddressType(ByRef objAddress As JulMar.Tapi3.TAddress) As Integer

        Dim nResult As Integer

        'prepare return value
        GetAddressType = 0

        'decide what address type to return

        Dim lAddressTypes As Integer

        lAddressTypes = objAddress.AddressCapability(JulMar.Tapi3.ADDRESS_CAPABILITY.AC_ADDRESSTYPES)
        nResult = PrintT3Result("GetAddressType: objITAddressCapabilities.AddressCapability(AC_ADDRESSTYPES)")
        If nResult <> NO_ERROR Then Exit Function

        Dim SelAddressType As Integer = VB6.GetItemData(cmbAddressType, cmbAddressType.SelectedIndex)

        If (SelAddressType And lAddressTypes) = 0 Then
            MsgBox("The selected provider does not support this address type.")
            Exit Function
        End If

        GetAddressType = SelAddressType

    End Function

    '
    'Finds out what are the default terminals for audio+capture and audio+render,
    'on the received address (there might be none);
    'makes an array with all of them, then puts them in the received variant;
    'If no terminal found for any of the audio+direction combinations,
    '"Nothing" (a NULL terminal pointer) will be set at the corresponding index.
    '
    Private Sub GetAudioTerminals(ByVal objAddress As JulMar.Tapi3.TAddress, ByRef rVarArrTerminals As Object)
        On Error Resume Next 'this will catch errors

        rVarArrTerminals = Nothing
        Dim nResult As Long

        '
        'put terminals in array, then put array in variant
        '

        'decide dimension of array
        'UPGRADE_WARNING: Lower bound of array arrTerminals was changed from 1 to 0. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="0F1C9BE1-AF9D-476E-83B1-17D43BECFF20"'
        Dim arrTerminals(1) As JulMar.Tapi3.TTerminal

        'put the array in a variant
        rVarArrTerminals = VB6.CopyArray(arrTerminals)


        'index 1 = the terminal for audio+capture
        rVarArrTerminals(0) = objAddress.GetDefaultStaticTerminal(JulMar.Tapi3.TAPIMEDIATYPES.AUDIO, JulMar.Tapi3.TERMINAL_DIRECTION.TD_CAPTURE)
        nResult = PrintT3Result("GetAudioTerminals: get default terminal for audio+capture")

        'index 2 = the terminal for audio+render
        rVarArrTerminals(1) = objAddress.GetDefaultStaticTerminal(JulMar.Tapi3.TAPIMEDIATYPES.AUDIO, JulMar.Tapi3.TERMINAL_DIRECTION.TD_RENDER)
        nResult = PrintT3Result("GetAudioTerminals: get default terminal for audio+render")


    End Sub

    '
    'It receives a variant that contains an array of terminals,
    'that might contain 0, 1 or 2 terminals (whatever was found as the
    'default terminals for audio+in and audio+out); actually the array
    'will always have 2 elements, which can be "Nothing" or "Not Nothing"
    '
    Private Sub ReleaseAudioTerminals(ByRef rVarArrTerminals As Object)
        On Error Resume Next 'this will catch errors

        Dim nIndex As Integer

        'release terminals

        If IsArray(rVarArrTerminals) Then
            For nIndex = LBound(rVarArrTerminals) To UBound(rVarArrTerminals)
                rVarArrTerminals(nIndex) = Nothing
            Next nIndex
        End If

    End Sub

    Private Sub pbGenerate_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles pbGenerate.Click
        On Error Resume Next 'this will catch errors

        System.Diagnostics.Debug.Assert((Not (mobjCall Is Nothing)), "")

        Dim nResult As Integer


        'call GenerateDigits; this might return errors, because we let the
        'user select any digit modes in the same time.

        If 0 = StrComp(txtDigitsToGenerate.Text, "Null", CompareMethod.Text) Then
            'give user a possibility to pass NULL string pointer as "txtDigitsToGenerate"
            Call mobjCall.GenerateDigits(vbNullString, GetDigitMode)
        ElseIf 0 = StrComp(txtDigitsToGenerate.Text, "Empty", CompareMethod.Text) Then
            'give user a possibility to pass an empty string ("") as "txtDigitsToGenerate"
            Call mobjCall.GenerateDigits("", GetDigitMode)
        Else
            Call mobjCall.GenerateDigits(txtDigitsToGenerate.Text, GetDigitMode)
        End If

        'print error, if any
        nResult = PrintT3Result("ITLegacyCallMediaControl.GenerateDigits")


    End Sub

    'Read value from "digit mode" check boxes, and or the corresponding
    'flags; this is usefull for parameter testing; unimodem should only work
    'with DTMF
    Function GetDigitMode() As Integer

        GetDigitMode = 0

        If cbModeDTMF.CheckState = System.Windows.Forms.CheckState.Checked Then
            GetDigitMode = GetDigitMode Or JulMar.Tapi3.LINEDIGITMODE.DTMF
        End If
        If cbModeDTMFEND.CheckState = System.Windows.Forms.CheckState.Checked Then
            GetDigitMode = GetDigitMode Or JulMar.Tapi3.LINEDIGITMODE.DTMFEND
        End If
        If cbModePulse.CheckState = System.Windows.Forms.CheckState.Checked Then
            GetDigitMode = GetDigitMode Or JulMar.Tapi3.LINEDIGITMODE.PULSE
        End If

    End Function

    Private Sub cbModeDTMF_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cbModeDTMF.CheckStateChanged
        If cbModeDTMF.CheckState = System.Windows.Forms.CheckState.Checked Then
            'display possible values
            txtDigitsToGenerate.Text = "0123456789ABCD*#"
        End If
    End Sub

    Private Sub cbModeDTMFEND_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cbModeDTMFEND.CheckStateChanged
        If cbModeDTMFEND.CheckState = System.Windows.Forms.CheckState.Checked Then
            'display possible values
            txtDigitsToGenerate.Text = "" 'no digits can be generated in DTMFEND mode
        End If
    End Sub

    Private Sub cbModePulse_CheckStateChanged(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles cbModePulse.CheckStateChanged
        If cbModePulse.CheckState = System.Windows.Forms.CheckState.Checked Then
            'display possible values
            txtDigitsToGenerate.Text = "0123456789"
        End If
    End Sub

    Private Sub pbStartDetect_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles pbStartDetect.Click
        On Error Resume Next 'this will catch errors

        System.Diagnostics.Debug.Assert((Not (mobjCall Is Nothing)), "")

        Dim nResult As Integer


        'call DetectDigits; this might return errors, because we let the
        'user select any digit modes.
        Call mobjCall.DetectDigits(GetDigitMode())

        'print error, if any
        nResult = PrintT3Result("ITLegacyCallMediaControl.DetectDigits" & "(" & GetDigitMode() & ")")


    End Sub

    Private Sub pbStopDetect_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles pbStopDetect.Click
        On Error Resume Next 'this will catch errors

        System.Diagnostics.Debug.Assert((Not (mobjCall Is Nothing)), "")

        Dim nResult As Integer

        'call DetectDigits(0); this might return errors
        Call mobjCall.DetectDigits(0)

        'print error, if any
        nResult = PrintT3Result("ITLegacyCallMediaControl.DetectDigits(0)")

    End Sub

    Function TranslateDigitMode(ByRef nDigitMode As Long) As String

        Select Case nDigitMode
            Case JulMar.Tapi3.LINEDIGITMODE.PULSE
                TranslateDigitMode = "LINEDIGITMODE_PULSE"
            Case JulMar.Tapi3.LINEDIGITMODE.DTMF
                TranslateDigitMode = "LINEDIGITMODE_DTMF"
            Case JulMar.Tapi3.LINEDIGITMODE.DTMFEND
                TranslateDigitMode = "LINEDIGITMODE_DTMFEND"
            Case Else
                TranslateDigitMode = "Unknown Digit Mode = " & nDigitMode & " !"
        End Select

    End Function

    Function TranslateGenerateTerm(ByRef lGenerationTermination As Long) As String

        Select Case lGenerationTermination
            Case LINEGENERATETERM_DONE
                TranslateGenerateTerm = "LINEGENERATETERM_DONE"
            Case LINEGENERATETERM_CANCEL
                TranslateGenerateTerm = "LINEGENERATETERM_CANCEL"
            Case Else
                TranslateGenerateTerm = "Unknown GenerationTermination value = " & lGenerationTermination & " !"
        End Select

    End Function

    Function TranslateCallMediaEvent(ByRef lCallMediaEvent As Long) As String

        Select Case lCallMediaEvent
            Case JulMar.Tapi3.CALL_MEDIA_EVENT.CME_NEW_STREAM
                TranslateCallMediaEvent = "CME_NEW_STREAM"
            Case JulMar.Tapi3.CALL_MEDIA_EVENT.CME_STREAM_ACTIVE
                TranslateCallMediaEvent = "CME_STREAM_ACTIVE"
            Case JulMar.Tapi3.CALL_MEDIA_EVENT.CME_STREAM_FAIL
                TranslateCallMediaEvent = "CME_STREAM_FAIL"
            Case JulMar.Tapi3.CALL_MEDIA_EVENT.CME_STREAM_INACTIVE
                TranslateCallMediaEvent = "CME_STREAM_INACTIVE"
            Case JulMar.Tapi3.CALL_MEDIA_EVENT.CME_STREAM_NOT_USED
                TranslateCallMediaEvent = "CME_STREAM_NOT_USED"
            Case JulMar.Tapi3.CALL_MEDIA_EVENT.CME_TERMINAL_FAIL
                TranslateCallMediaEvent = "CME_TERMINAL_FAIL"
            Case Else
                TranslateCallMediaEvent = "Unknown CallMediaEvent = " & lCallMediaEvent & " !"
        End Select

    End Function

    Function TranslateCallMediaEventCause(ByRef lCallMediaEventCause As Long) As String

        Select Case lCallMediaEventCause
            Case JulMar.Tapi3.CALL_MEDIA_EVENT_CAUSE.CMC_BAD_DEVICE
                TranslateCallMediaEventCause = "CMC_BAD_DEVICE"
            Case JulMar.Tapi3.CALL_MEDIA_EVENT_CAUSE.CMC_CONNECT_FAIL
                TranslateCallMediaEventCause = "CMC_CONNECT_FAIL"
            Case JulMar.Tapi3.CALL_MEDIA_EVENT_CAUSE.CMC_LOCAL_REQUEST
                TranslateCallMediaEventCause = "CMC_LOCAL_REQUEST"
            Case JulMar.Tapi3.CALL_MEDIA_EVENT_CAUSE.CMC_MEDIA_RECOVERED
                TranslateCallMediaEventCause = "CMC_MEDIA_RECOVERED"
            Case JulMar.Tapi3.CALL_MEDIA_EVENT_CAUSE.CMC_MEDIA_TIMEOUT
                TranslateCallMediaEventCause = "CMC_MEDIA_TIMEOUT"
            Case JulMar.Tapi3.CALL_MEDIA_EVENT_CAUSE.CMC_REMOTE_REQUEST
                TranslateCallMediaEventCause = "CMC_REMOTE_REQUEST"
            Case JulMar.Tapi3.CALL_MEDIA_EVENT_CAUSE.CMC_UNKNOWN
                TranslateCallMediaEventCause = "CMC_UNKNOWN"
            Case Else
                TranslateCallMediaEventCause = "Unknown CallMediaEventCause = " & lCallMediaEventCause & " !"
        End Select

    End Function

    'Looks in combo with addresses and sees what address was selected.
    'Looks in the related "data" field and finds out the index memorized for
    'that address. This index represents the index in the objTapi.objcollAddresses.
    'Return 0 if no address is selected.
    'Otherwise return its index, which should be a value between 1 and Addresses.Count
    Private Function FindOriginationAddressIndex() As Integer
        On Error Resume Next 'this will catch errors

        Dim nResult As Integer
        Dim indexAddr As Integer

        'prepare return value
        FindOriginationAddressIndex = 0

        If cmbAddresses.Items.Count > 0 Then

            'read data field of selected combo item
            indexAddr = VB6.GetItemData(cmbAddresses, cmbAddresses.SelectedIndex)
            nResult = PrintT3Result("FindOriginationAddressIndex: retrieve selected address from combo")

            If nResult = NO_ERROR Then
                FindOriginationAddressIndex = indexAddr
            End If
        End If

        Exit Function
    End Function

    'Returns the last tapi3 error that caused the function to fail,
    'or NO_ERROR if there were no tapi3 failures.
    '(i.e.: don't return error codes produced inside error handlers)
    Private Function InitializeTapiObjects() As Integer
        On Error Resume Next

        Dim nResult As Integer

        If mbInitialized = True Then
            InitializeTapiObjects = NO_ERROR
            Exit Function
        End If

        txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
        txtStatus.Text = txtStatus.Text & "Tapi initialization: start..."

        txtStatus.SelectionStart = Len(txtStatus.Text)
        txtStatus.SelectionLength = 0

        Me.Refresh()


        'call Initialize; this must be called before
        'any other tapi functions are called.

        mobjTapi.Initialize()


        nResult = PrintT3Result("objTapi.Initialize")
        If nResult <> NO_ERROR Then

            PrintT3Result("Release objTapi")

            GoTo ErrorExit
        End If



NormalExit:
        txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
        txtStatus.Text = txtStatus.Text & "Tapi initialization: finished."

        txtStatus.SelectionStart = Len(txtStatus.Text)
        txtStatus.SelectionLength = 0

        Me.Refresh()

        mbInitialized = True
        InitializeTapiObjects = NO_ERROR
        Exit Function

ErrorExit:
        txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
        txtStatus.Text = txtStatus.Text & "Tapi initialization: failed."

        txtStatus.SelectionStart = Len(txtStatus.Text)
        txtStatus.SelectionLength = 0

        Me.Refresh()

        mbInitialized = False
        InitializeTapiObjects = nResult
        Exit Function
    End Function

    Private Function ReleaseAllMembers() As Integer

        If mbInitialized = False Then
            Exit Function
        End If

        'release all member objects

        mobjCall = Nothing

        Call ReleaseAudioTerminals(mvarArrAudioTerminals)

        mobjOrigAddress = Nothing

        System.Diagnostics.Debug.Assert((Not (mobjTapi Is Nothing)), "")

        mobjTapi.Shutdown()

        mobjTapi = Nothing

    End Function

    '
    'This function receives a call object and an array with the terminals
    'to be selected;
    '- it first queries the stream control object from the call object;
    '- it then selects each terminal on a stream that matches
    'the media type and the terminal direction.
    '
    'If an error is encountered, the function finishes right away and returns
    'that error.
    '
    'Notes:
    ' 1 - the received array might contain "Null" terminals (the value Nothing)
    'in its items - so we need to check the termials before using them.
    ' 2 - ITStreamControl is not supported on all addresses (depending on the TSP)
    'therefore querying for this interface might fail.
    '
    Public Function SelectTerminalsOnStreams(ByRef objITBCC As JulMar.Tapi3.TCall, ByRef varArrTerminals As Object) As TestError
        On Error Resume Next

        Dim MyError As TestError
        SelectTerminalsOnStreams = TestError.TErr_Ok

        Dim nTermIndex As Integer

        'get streams collection object

        Dim objITCollStreams() As JulMar.Tapi3.TStream

        objITCollStreams = objITBCC.Streams
        MyError = PrintT3Result("objITStreamControl.Streams")
        If MyError <> 0 Then
            SelectTerminalsOnStreams = TestError.TErr_Fail
            Exit Function
        End If

        'find matching stream for each terminal and select the terminal

        Dim objCrtITStream As JulMar.Tapi3.TStream

        For nTermIndex = LBound(varArrTerminals) To UBound(varArrTerminals)

            If Not (varArrTerminals(nTermIndex) Is Nothing) Then

                'find matching stream
                MyError = FindMatchingStream(objITCollStreams, varArrTerminals(nTermIndex), objCrtITStream)
                If MyError = TestError.TErr_Fail Then
                    SelectTerminalsOnStreams = TestError.TErr_Fail
                    Exit Function
                End If

                'select terminal
                Call objCrtITStream.SelectTerminal(varArrTerminals(nTermIndex))
                MyError = PrintT3Result("objCrtITStream.SelectTerminal")
                If MyError <> 0 Then
                    SelectTerminalsOnStreams = TestError.TErr_Fail
                    Exit Function
                End If

            End If

        Next nTermIndex

    End Function

    '
    'This function searches in objITCollStreams the first stream that matches
    'the "media type" and "direction" specified by objITTerminal;
    'if it finds such a stream, it returns a reference to it;
    'otherwise it returns "Nothing"
    '
    Private Function FindMatchingStream(ByVal objITCollStreams() As JulMar.Tapi3.TStream, ByVal objITTerminal As JulMar.Tapi3.TTerminal, ByRef robjITStream As JulMar.Tapi3.TStream) As TestError
        On Error Resume Next

        Dim MyError As TestError
        FindMatchingStream = TestError.TErr_Ok

        'initialize return value
        'UPGRADE_NOTE: Object robjITStream may not be destroyed until it is garbage collected. Click for more: 'ms-help://MS.VSCC.v80/dv_commoner/local/redirect.htm?keyword="6E35BFF6-CD74-4B09-9689-3E1A43DF8969"'
        robjITStream = Nothing

        'read media type and direction from terminal

        Dim lMediaType As Integer
        Dim lDirection As JulMar.Tapi3.TERMINAL_DIRECTION

        lMediaType = objITTerminal.MediaType
        MyError = PrintT3Result("objITTerminal.MediaType")
        If MyError <> 0 Then
            FindMatchingStream = TestError.TErr_Fail
            Exit Function
        End If

        lDirection = objITTerminal.Direction
        MyError = PrintT3Result("objITTerminal.Direction")
        If MyError <> 0 Then
            FindMatchingStream = TestError.TErr_Fail
            Exit Function
        End If

        'search stream that matches this media and direction

        Dim nCount, nIndex As Integer
        Dim objCrtStream As JulMar.Tapi3.TStream
        Dim lCrtMediaType As Integer
        Dim lCrtDirection As JulMar.Tapi3.TERMINAL_DIRECTION

        nCount = objITCollStreams.Length
        MyError = PrintT3Result("objITCollStreams.Count")
        If MyError <> 0 Then
            FindMatchingStream = TestError.TErr_Fail
            Exit Function
        End If

        For nIndex = 0 To nCount - 1

            objCrtStream = objITCollStreams(nIndex)
            MyError = PrintT3Result("objITCollStreams.Item(nIndex)")
            If MyError <> 0 Then
                FindMatchingStream = TestError.TErr_Fail
                Exit Function
            End If

            lCrtMediaType = objCrtStream.MediaType
            MyError = PrintT3Result("objCrtStream.MediaType")
            If MyError <> 0 Then
                FindMatchingStream = TestError.TErr_Fail
                Exit Function
            End If

            lCrtDirection = objCrtStream.Direction
            MyError = PrintT3Result("objCrtStream.Direction")
            If MyError <> 0 Then
                FindMatchingStream = TestError.TErr_Fail
                Exit Function
            End If

            If lMediaType = lCrtMediaType And lDirection = lCrtDirection Then
                'set return value
                robjITStream = objCrtStream
                PrintT3Result("Set robjITStream = objCrtStream")

                'quit loop, we're done
                Exit For
            End If

        Next nIndex

        Exit Function
    End Function

    'Reads the last error from Err object
    'If Err.Number = 0, it means that no error had occurred.
    'Returns the error code found in Err.Number when this function is called.
    'Before returning, it clears the error.
    '
    Private Function PrintT3Result(ByRef strT3Action As String) As Integer

        PrintT3Result = NO_ERROR

        'log the tapi3 function name that produced this result
        'and, if error, print also error number + description

        PrintT3Result = Err.Number

        Dim strError As String

        If Err.Number = NO_ERROR Then
            strError = "Succes: "
            strError = strError & strT3Action

            'success has low logging level
            Debug.Print(strError)
        Else
            strError = "Error: "
            strError = strError & strT3Action & " Err.Number = 0x" & Hex(Err.Number)
            strError = strError & " Err.Descripton = " & Err.Description

            'error has high logging level
            Debug.Print(strError)
            txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
            txtStatus.Text = txtStatus.Text & strError

            txtStatus.SelectionStart = Len(txtStatus.Text)
            txtStatus.SelectionLength = 0

        End If

        Err.Clear()

    End Function

    Private Sub mobjTapi_TE_CALLMEDIA(ByVal sender As Object, ByVal e As JulMar.Tapi3.TapiCallMediaEventArgs) Handles mobjTapi.TE_CALLMEDIA
        On Error Resume Next 'this will catch errors
        Dim nResult As Integer
        Dim lEvent As JulMar.Tapi3.CALL_MEDIA_EVENT
        Dim lCause As JulMar.Tapi3.CALL_MEDIA_EVENT_CAUSE
        Dim lError As Integer
        Dim strStreamName, strTermName As String
        Dim lStreamMediaType, lTermMediaType As Integer
        Dim lStreamDirection, lTermDirection As JulMar.Tapi3.TERMINAL_DIRECTION
        Dim objCurrentCallInfo As JulMar.Tapi3.TCall
        Dim objReceivedCallInfo As JulMar.Tapi3.TCall
        Dim strMsg, strCallInfoMsg As String


        nResult = PrintT3Result("mobjTapiWithEvents_Event: Set objITCallMediaEvent = pEvent")
        If nResult <> NO_ERROR Then Exit Sub

        lEvent = e.Event
        nResult = PrintT3Result("mobjTapiWithEvents_Event: objITCallMediaEvent.Event")
        If nResult <> NO_ERROR Then Exit Sub

        lCause = e.Cause
        nResult = PrintT3Result("mobjTapiWithEvents_Event: objITCallMediaEvent.Cause")
        If nResult <> NO_ERROR Then Exit Sub

        If Not e.Error Is Nothing Then
            lError = e.Error.ErrorCode
            nResult = PrintT3Result("mobjTapiWithEvents_Event: objITCallMediaEvent.Error")
            If nResult <> NO_ERROR Then Exit Sub
        End If


        If Not (e.Stream Is Nothing) Then
            strStreamName = e.Stream.Name
            nResult = PrintT3Result("mobjTapiWithEvents_Event: objITCallMediaEvent.Stream.Name")
            If nResult <> NO_ERROR Then Exit Sub

            lStreamMediaType = e.Stream.MediaType
            nResult = PrintT3Result("mobjTapiWithEvents_Event: objITCallMediaEvent.Stream.MediaType")
            If nResult <> NO_ERROR Then Exit Sub

            lStreamDirection = e.Stream.Direction
            nResult = PrintT3Result("mobjTapiWithEvents_Event: objITCallMediaEvent.Stream.Direction")
            If nResult <> NO_ERROR Then Exit Sub

        Else
            strStreamName = "no stream"
        End If

        If Not (e.Terminal Is Nothing) Then
            strTermName = e.Terminal.Name
            nResult = PrintT3Result("mobjTapiWithEvents_Event: objITCallMediaEvent.Terminal.Name")
            If nResult <> NO_ERROR Then Exit Sub

            lTermMediaType = e.Terminal.MediaType
            nResult = PrintT3Result("mobjTapiWithEvents_Event: objITCallMediaEvent.Terminal.MediaType")
            If nResult <> NO_ERROR Then Exit Sub

            lTermDirection = e.Terminal.Direction
            nResult = PrintT3Result("mobjTapiWithEvents_Event: objITCallMediaEvent.Terminal.Direction")
            If nResult <> NO_ERROR Then Exit Sub

        Else
            strTermName = "no terminal"
        End If

        '
        objReceivedCallInfo = e.Call
        nResult = PrintT3Result("mobjTapiWithEvents_Event: objITCallMediaEvent.Call")
        If nResult <> NO_ERROR Then Exit Sub

        '
        'check if the received CallInfo matches the call
        'for which our app currently keeps a reference of.
        '
        objCurrentCallInfo = mobjCall
        nResult = PrintT3Result("mobjTapiWithEvents_Event: Set objCurrentCallInfo = mobjCall")
        If nResult <> NO_ERROR Then Exit Sub

        If objCurrentCallInfo Is objReceivedCallInfo Then
            strCallInfoMsg = "matches current call"
        Else
            strCallInfoMsg = "doesn't match current call! (error)"
            MsgBox("Call object received in TE_CALLMEDIA doesn't match current call!")
        End If

        strMsg = "Event type = TE_CALLMEDIA: "
        strMsg = strMsg & Chr(13) & Chr(10)

        strMsg = strMsg & "  " & "lEvent = 0x" & Hex(lEvent) & " " & TranslateCallMediaEvent(lEvent) & ", " & "lCause = 0x" & Hex(lCause) & " " & TranslateCallMediaEventCause(lCause) & ", " & "lError = 0x" & Hex(lError) & " "
        strMsg = strMsg & Chr(13) & Chr(10)

        strMsg = strMsg & "  " & "stream = " & "'" & strStreamName & "'" & ", " & "mediatype = 0x" & Hex(lStreamMediaType) & ", " & "direction = 0x" & Hex(lStreamDirection) & " "
        strMsg = strMsg & Chr(13) & Chr(10)

        strMsg = strMsg & "  " & "terminal = " & "'" & strTermName & "'" & ", " & "mediatype = 0x" & Hex(lTermMediaType) & ", " & "direction = 0x" & Hex(lTermDirection) & " "
        strMsg = strMsg & Chr(13) & Chr(10)

        strMsg = strMsg & "  objCallInfo = " & strCallInfoMsg & " "
        strMsg = strMsg & Chr(13) & Chr(10)

        txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
        txtStatus.Text = txtStatus.Text & strMsg

        txtStatus.SelectionStart = Len(txtStatus.Text)
        txtStatus.SelectionLength = 0


    End Sub

    Private Sub mobjTapi_TE_CALLSTATE(ByVal sender As Object, ByVal e As JulMar.Tapi3.TapiCallStateEventArgs) Handles mobjTapi.TE_CALLSTATE
        On Error Resume Next 'this will catch errors
        Dim nResult As Integer
        Dim CallState As JulMar.Tapi3.CALL_STATE

        '
        'process CallStateEvent-s
        '

        nResult = PrintT3Result("mobjTapiWithEvents_Event: Set objCallStateEvent = pEvent")
        If nResult <> NO_ERROR Then
            Call MsgBox("Fatal error: can't query for call state event, exit program", MsgBoxStyle.Critical)
            Stop 'fatal error
        End If

        CallState = e.State
        nResult = PrintT3Result("mobjTapiWithEvents_Event: objCallStateEvent.State")
        If nResult <> NO_ERROR Then
            Call MsgBox("Fatal error: can't retrieve new call state, exit program", MsgBoxStyle.Critical)
            Stop 'fatal error
        End If

        PrintCallState((CallState))

        If CallState = JulMar.Tapi3.CALL_STATE.CS_DISCONNECTED Then
            '
            'don't release call here, let the user do this by pressing "Release"
            '
            '        'release call, you don't need it anymore
            '        Set mobjCall = Nothing
            '
            '        'update UI
            '        pbDial.Enabled = True
            '        pbDisconnect.Enabled = False
            '        pbRelease.Enabled = False
            '
            '        pbGenerate.Enabled = False
            '        pbStartDetect.Enabled = False
            '        pbStopDetect.Enabled = False

            '
            'but since call was disconnected, we still need to update the UI
            '
            'update UI
            pbDisconnect.Enabled = False
            pbRelease.Enabled = True

        End If


    End Sub

    Private Sub mobjTapi_TE_DIGITEVENT(ByVal sender As Object, ByVal e As JulMar.Tapi3.TapiDigitDetectionEventArgs) Handles mobjTapi.TE_DIGITEVENT
        On Error Resume Next 'this will catch errors
        Dim nResult As Integer
        Dim bDigit As Byte
        Dim lDigitMode As Integer
        Dim lTickCount As Integer
        Dim objCurrentCallInfo As JulMar.Tapi3.TCall
        Dim objReceivedCallInfo As JulMar.Tapi3.TCall
        Dim strMsg, strCallInfoMsg As String


        nResult = PrintT3Result("mobjTapiWithEvents_Event: Set objITDigitDetectionEvent = pEvent")
        If nResult <> NO_ERROR Then Exit Sub

        bDigit = e.Digit
        nResult = PrintT3Result("mobjTapiWithEvents_Event: objITDigitDetectionEvent.Digit")
        If nResult <> NO_ERROR Then Exit Sub

        lDigitMode = e.DigitMode
        nResult = PrintT3Result("mobjTapiWithEvents_Event: objITDigitDetectionEvent.DigitMode")
        If nResult <> NO_ERROR Then Exit Sub

        lTickCount = e.TickCount
        nResult = PrintT3Result("mobjTapiWithEvents_Event: objITDigitDetectionEvent.TickCount")
        If nResult <> NO_ERROR Then Exit Sub


        objReceivedCallInfo = e.Call
        nResult = PrintT3Result("mobjTapiWithEvents_Event: objITDigitDetectionEvent.Call")
        If nResult <> NO_ERROR Then Exit Sub

        '
        'check if the received CallInfo matches the call
        'for which our app currently keeps a reference of.
        '
        objCurrentCallInfo = mobjCall
        nResult = PrintT3Result("mobjTapiWithEvents_Event: Set objCurrentCallInfo = mobjCall")
        If nResult <> NO_ERROR Then Exit Sub

        If objCurrentCallInfo Is objReceivedCallInfo Then
            strCallInfoMsg = "matches current call"
        Else
            strCallInfoMsg = "doesn't match current call! (error)"
            MsgBox("Call object received in TE_DIGITEVENT doesn't match current call!")
        End If

        strMsg = "Event type = TE_DIGITEVENT: "
        strMsg = strMsg & Chr(13) & Chr(10)

        strMsg = strMsg & "  bDigit = 0x" & Hex(bDigit) & " "
        strMsg = strMsg & Chr(13) & Chr(10)

        strMsg = strMsg & "  lDigitMode = " & lDigitMode & " " & TranslateDigitMode(lDigitMode) & " "
        strMsg = strMsg & Chr(13) & Chr(10)

        strMsg = strMsg & "  lTickCount = 0x" & Hex(lTickCount) & " "
        strMsg = strMsg & Chr(13) & Chr(10)

        strMsg = strMsg & "  objCallInfo = " & strCallInfoMsg & " "
        strMsg = strMsg & Chr(13) & Chr(10)

        txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
        txtStatus.Text = txtStatus.Text & strMsg

        txtStatus.SelectionStart = Len(txtStatus.Text)
        txtStatus.SelectionLength = 0

    End Sub

    Private Sub mobjTapi_TE_GENERATEEVENT(ByVal sender As Object, ByVal e As JulMar.Tapi3.TapiDigitGenerationEventArgs) Handles mobjTapi.TE_GENERATEEVENT
        On Error Resume Next 'this will catch errors
        Dim strMsg, strCallInfoMsg As String
        Dim nResult As Integer
        Dim objCurrentCallInfo As JulMar.Tapi3.TCall
        Dim objReceivedCallInfo As JulMar.Tapi3.TCall
        Dim lGenerationTermination, lTickCount As Integer


        nResult = PrintT3Result("mobjTapiWithEvents_Event: Set objITDigitGenerationEvent = pEvent")
        If nResult <> NO_ERROR Then Exit Sub

        lGenerationTermination = e.GenerationTermination
        nResult = PrintT3Result("mobjTapiWithEvents_Event: objITDigitGenerationEvent.GenerationTermination")
        If nResult <> NO_ERROR Then Exit Sub

        lTickCount = e.TickCount
        nResult = PrintT3Result("mobjTapiWithEvents_Event: objITDigitGenerationEvent.TickCount")
        If nResult <> NO_ERROR Then Exit Sub


        objReceivedCallInfo = e.Call
        nResult = PrintT3Result("mobjTapiWithEvents_Event: objITDigitGenerationEvent.Call")
        If nResult <> NO_ERROR Then Exit Sub

        '
        'check if the received CallInfo matches the call
        'for which our app currently keeps a reference of.
        '
        objCurrentCallInfo = mobjCall
        nResult = PrintT3Result("mobjTapiWithEvents_Event: Set objCurrentCallInfo = mobjCall")
        If nResult <> NO_ERROR Then Exit Sub

        If objCurrentCallInfo Is objReceivedCallInfo Then
            strCallInfoMsg = "matches current call"
        Else
            strCallInfoMsg = "doesn't match current call! (error)"
            MsgBox("Call object received in TE_GENERATEEVENT doesn't match current call!")
        End If

        strMsg = "Event type = TE_GENERATEEVENT: "
        strMsg = strMsg & Chr(13) & Chr(10)

        strMsg = strMsg & "  lGenerationTermination = " & lGenerationTermination & " " & TranslateGenerateTerm(lGenerationTermination) & " "
        strMsg = strMsg & Chr(13) & Chr(10)

        strMsg = strMsg & "  lTickCount = 0x" & Hex(lTickCount) & " "
        strMsg = strMsg & Chr(13) & Chr(10)

        strMsg = strMsg & "  objCallInfo = " & strCallInfoMsg & " "
        strMsg = strMsg & Chr(13) & Chr(10)

        txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
        txtStatus.Text = txtStatus.Text & strMsg

        txtStatus.SelectionStart = Len(txtStatus.Text)
        txtStatus.SelectionLength = 0

    End Sub
End Class