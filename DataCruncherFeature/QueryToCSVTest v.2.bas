'****************************************************************
'Microsoft SQL Server 2000
'Visual Basic file generated for DTS Package
'File Name: \\Sligofileserver\F\CLIENTS\Wisconsin\DataDownloadFeature\QueryToCSVTest v.2.bas
'Package Name: QueryToCSVTest v.2
'Package Description: 
'Generated Date: 9/22/2004
'Generated Time: 4:57:51 PM
'****************************************************************

Option Explicit
Public goPackageOld As New DTS.Package
Public goPackage As DTS.Package2
Private Sub Main()
	set goPackage = goPackageOld

	goPackage.Name = "QueryToCSVTest v.2"
	goPackage.WriteCompletionStatusToNTEventLog = False
	goPackage.FailOnError = False
	goPackage.PackagePriorityClass = 2
	goPackage.MaxConcurrentSteps = 4
	goPackage.LineageOptions = 0
	goPackage.UseTransaction = True
	goPackage.TransactionIsolationLevel = 4096
	goPackage.AutoCommitTransaction = True
	goPackage.RepositoryMetadataOptions = 0
	goPackage.UseOLEDBServiceComponents = True
	goPackage.LogToSQLServer = False
	goPackage.LogServerFlags = 0
	goPackage.FailPackageOnLogFailure = False
	goPackage.ExplicitGlobalVariables = False
	goPackage.PackageType = 0
	


'---------------------------------------------------------------------------
' create package connection information
'---------------------------------------------------------------------------

Dim oConnection as DTS.Connection2

'------------- a new connection defined below.
'For security purposes, the password is never scripted

Set oConnection = goPackage.Connections.New("SQLOLEDB")

	oConnection.ConnectionProperties("Integrated Security") = "SSPI"
	oConnection.ConnectionProperties("Persist Security Info") = True
	oConnection.ConnectionProperties("Initial Catalog") = "Northwind"
	oConnection.ConnectionProperties("Data Source") = "(local)"
	oConnection.ConnectionProperties("Application Name") = "DTS Designer"
	
	oConnection.Name = "Microsoft OLE DB Provider for SQL Server"
	oConnection.ID = 3
	oConnection.Reusable = True
	oConnection.ConnectImmediate = False
	oConnection.DataSource = "(local)"
	oConnection.ConnectionTimeout = 60
	oConnection.Catalog = "Northwind"
	oConnection.UseTrustedConnection = True
	oConnection.UseDSL = False
	
	'If you have a password for this connection, please uncomment and add your password below.
	'oConnection.Password = "<put the password here>"

goPackage.Connections.Add oConnection
Set oConnection = Nothing

'------------- a new connection defined below.
'For security purposes, the password is never scripted

Set oConnection = goPackage.Connections.New("SQLOLEDB")

	oConnection.ConnectionProperties("Integrated Security") = "SSPI"
	oConnection.ConnectionProperties("Persist Security Info") = True
	oConnection.ConnectionProperties("Initial Catalog") = "Northwind"
	oConnection.ConnectionProperties("Data Source") = "(local)"
	oConnection.ConnectionProperties("Application Name") = "DTS Designer"
	
	oConnection.Name = "Microsoft OLE DB Provider for SQL Server 2"
	oConnection.ID = 4
	oConnection.Reusable = True
	oConnection.ConnectImmediate = False
	oConnection.DataSource = "(local)"
	oConnection.ConnectionTimeout = 60
	oConnection.Catalog = "Northwind"
	oConnection.UseTrustedConnection = True
	oConnection.UseDSL = False
	
	'If you have a password for this connection, please uncomment and add your password below.
	'oConnection.Password = "<put the password here>"

goPackage.Connections.Add oConnection
Set oConnection = Nothing

'---------------------------------------------------------------------------
' create package steps information
'---------------------------------------------------------------------------

Dim oStep as DTS.Step2
Dim oPrecConstraint as DTS.PrecedenceConstraint

'------------- a new step defined below

Set oStep = goPackage.Steps.New

	oStep.Name = "DTSStep_DTSDataPumpTask_1"
	oStep.Description = "Transform Data Task: undefined"
	oStep.ExecutionStatus = 4
	oStep.TaskName = "DTSTask_DTSDataPumpTask_1"
	oStep.CommitSuccess = False
	oStep.RollbackFailure = False
	oStep.ScriptLanguage = "VBScript"
	oStep.AddGlobalVariables = True
	oStep.RelativePriority = 3
	oStep.CloseConnection = False
	oStep.ExecuteInMainThread = False
	oStep.IsPackageDSORowset = False
	oStep.JoinTransactionIfPresent = False
	oStep.DisableStep = False
	oStep.FailPackageOnError = False
	
goPackage.Steps.Add oStep
Set oStep = Nothing

'---------------------------------------------------------------------------
' create package tasks information
'---------------------------------------------------------------------------

'------------- call Task_Sub1 for task DTSTask_DTSDataPumpTask_1 (Transform Data Task: undefined)
Call Task_Sub1( goPackage	)

'---------------------------------------------------------------------------
' Save or execute package
'---------------------------------------------------------------------------

'goPackage.SaveToSQLServer "(local)", "sa", ""
goPackage.Execute
tracePackageError goPackage
goPackage.Uninitialize
'to save a package instead of executing it, comment out the executing package lines above and uncomment the saving package line
set goPackage = Nothing

set goPackageOld = Nothing

End Sub


'-----------------------------------------------------------------------------
' error reporting using step.GetExecutionErrorInfo after execution
'-----------------------------------------------------------------------------
Public Sub tracePackageError(oPackage As DTS.Package)
Dim ErrorCode As Long
Dim ErrorSource As String
Dim ErrorDescription As String
Dim ErrorHelpFile As String
Dim ErrorHelpContext As Long
Dim ErrorIDofInterfaceWithError As String
Dim i As Integer

	For i = 1 To oPackage.Steps.Count
		If oPackage.Steps(i).ExecutionResult = DTSStepExecResult_Failure Then
			oPackage.Steps(i).GetExecutionErrorInfo ErrorCode, ErrorSource, ErrorDescription, _
					ErrorHelpFile, ErrorHelpContext, ErrorIDofInterfaceWithError
			MsgBox oPackage.Steps(i).Name & " failed" & vbCrLf & ErrorSource & vbCrLf & ErrorDescription
		End If
	Next i

End Sub

'------------- define Task_Sub1 for task DTSTask_DTSDataPumpTask_1 (Transform Data Task: undefined)
Public Sub Task_Sub1(ByVal goPackage As Object)

Dim oTask As DTS.Task
Dim oLookup As DTS.Lookup

Dim oCustomTask1 As DTS.DataPumpTask2
Set oTask = goPackage.Tasks.New("DTSDataPumpTask")
oTask.Name = "DTSTask_DTSDataPumpTask_1"
Set oCustomTask1 = oTask.CustomTask

	oCustomTask1.Name = "DTSTask_DTSDataPumpTask_1"
	oCustomTask1.Description = "Transform Data Task: undefined"
	oCustomTask1.SourceConnectionID = 3
	oCustomTask1.SourceSQLStatement = "select " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'Query' = " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(OrderID as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(CustomerID as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(EmployeeID as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(OrderDate as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(RequiredDate as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(ShippedDate as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(ShipVia as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(Freight as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(ShipName as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(ShipAddress as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(ShipCity as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(ShipRegion as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(ShipPostalCode as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(ShipCountry as varchar),'') + '"",' + char(13) + char(10) , " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'Filename' = 'testcsv.csv'" & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "from orders" & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "union" & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "select " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'Query' = " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(OrderID as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(CustomerID as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(EmployeeID as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(OrderDate as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(RequiredDate as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(ShippedDate as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(ShipVia as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(Freight as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(ShipName as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(ShipAddress as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(ShipCity as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(ShipRegion as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(ShipPostalCode as varchar),'') + '"",' + " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'""' + isnull(cast(ShipCountry as varchar),'') + '"",' + char(13) + char(10) , " & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "'Filename' = 'testcsvs.csv'" & vbCrLf
	oCustomTask1.SourceSQLStatement = oCustomTask1.SourceSQLStatement & "from orders"
	oCustomTask1.DestinationConnectionID = 4
	oCustomTask1.DestinationObjectName = "[Northwind].[dbo].[Orders]"
	oCustomTask1.ProgressRowCount = 1000
	oCustomTask1.MaximumErrorCount = 0
	oCustomTask1.FetchBufferSize = 1
	oCustomTask1.UseFastLoad = True
	oCustomTask1.InsertCommitSize = 0
	oCustomTask1.ExceptionFileColumnDelimiter = "|"
	oCustomTask1.ExceptionFileRowDelimiter = vbCrLf
	oCustomTask1.AllowIdentityInserts = False
	oCustomTask1.FirstRow = 0
	oCustomTask1.LastRow = 0
	oCustomTask1.FastLoadOptions = 2
	oCustomTask1.ExceptionFileOptions = 1
	oCustomTask1.DataPumpOptions = 0
	
Call oCustomTask1_Trans_Sub1( oCustomTask1	)
		
		
goPackage.Tasks.Add oTask
Set oCustomTask1 = Nothing
Set oTask = Nothing

End Sub

Public Sub oCustomTask1_Trans_Sub1(ByVal oCustomTask1 As Object)

	Dim oTransformation As DTS.Transformation2
	Dim oTransProps as DTS.Properties
	Dim oColumn As DTS.Column
	Set oTransformation = oCustomTask1.Transformations.New("DTSPump.DataPumpTransformWriteFile")
		oTransformation.Name = "DTSTransformation__1"
		oTransformation.TransformFlags = 63
		oTransformation.ForceSourceBlobsBuffered = 0
		oTransformation.ForceBlobsInMemory = False
		oTransformation.InMemoryBlobSize = 1048576
		oTransformation.TransformPhases = 4
		
		Set oColumn = oTransformation.SourceColumns.New("Filename" , 1)
			oColumn.Name = "Filename"
			oColumn.Ordinal = 1
			oColumn.Flags = 0
			oColumn.Size = 20
			oColumn.DataType = 129
			oColumn.Precision = 0
			oColumn.NumericScale = 0
			oColumn.Nullable = False
			
		oTransformation.SourceColumns.Add oColumn
		Set oColumn = Nothing

		Set oColumn = oTransformation.SourceColumns.New("Query" , 2)
			oColumn.Name = "Query"
			oColumn.Ordinal = 2
			oColumn.Flags = 0
			oColumn.Size = 462
			oColumn.DataType = 129
			oColumn.Precision = 0
			oColumn.NumericScale = 0
			oColumn.Nullable = False
			
		oTransformation.SourceColumns.Add oColumn
		Set oColumn = Nothing

	Set oTransProps = oTransformation.TransformServerProperties

		oTransProps("ErrorIfFileExists") = False
		oTransProps("AppendIfFileExists") = True
		oTransProps("FilePath") = "C:\scrap"
		oTransProps("FileColumnName") = "Filename"
		oTransProps("UnicodeFile") = False
		oTransProps("OEMFile") = False
		
	Set oTransProps = Nothing

	oCustomTask1.Transformations.Add oTransformation
	Set oTransformation = Nothing

End Sub

