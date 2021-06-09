#pragma once
#include<msclr/marshal_cppstd.h>
#include <string>
namespace SocketUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::IO;
	using namespace System::Runtime::InteropServices;


	delegate void DelADDCLIENT(String^,bool);
	delegate void DelADDQUEUE(array< String^>^);
	delegate void DelProgressBar(int,int);
	delegate void DelCompelete(int);


	[UnmanagedFunctionPointerAttribute(CallingConvention::Cdecl)]
	delegate void UIChangeProgress(int queueid, int value);
	[UnmanagedFunctionPointerAttribute(CallingConvention::Cdecl)]
	delegate void UINewClient(std::string, bool flag);
	[UnmanagedFunctionPointerAttribute(CallingConvention::Cdecl)]
	delegate void UINewRecieve(int Queueid, std::string Name, std::string Extention);


	[DllImport("ServerDLL.dll" , CallingConvention = CallingConvention::Cdecl)]
	 void  Startup(std::string , int , UIChangeProgress^, UINewClient^, UINewRecieve^);

	 [DllImport("ServerDLL.dll", CallingConvention = CallingConvention::Cdecl)]
	 int SendFile(std::string path, std::string username);

	 [DllImport("ServerDLL.dll", CallingConvention = CallingConvention::Cdecl)]
	 void StartDownload(int queueid);

	public ref class MyForm : public System::Windows::Forms::Form
	{
		DelADDCLIENT^ Event_ADDCLIENT;
		DelADDQUEUE^ Event_ADDQUEUE;
		DelProgressBar^ Event_Progress;
		UIChangeProgress^ Event_UIChangeProgress;
		UINewClient^ Event_UINewClient;
		UINewRecieve^ Event_UINewRecieve;
		DelCompelete^ Event_Compelete;
		bool IsRunning;
		bool IsTransfer;
	public:MyForm()
		{
			InitializeComponent();
			Rigster();
			IsRunning = false;
			IsTransfer = false;
		}
		  void Rigster()
		  {
			  Event_ADDCLIENT += gcnew DelADDCLIENT(this, &MyForm::AddClient);
			  Event_ADDQUEUE	+= gcnew DelADDQUEUE(this, &MyForm::AddNewQueue);
			  Event_Progress += gcnew DelProgressBar(this, &MyForm::ChangeProgress);
			  Event_UIChangeProgress += gcnew UIChangeProgress(this, &MyForm::ChangeProgress);
			  Event_UINewClient += gcnew UINewClient(this, &MyForm::ChangeClient);
			  Event_UINewRecieve += gcnew UINewRecieve(this, &MyForm::NewQueueRow);
			  Event_Compelete += gcnew DelCompelete(this, &MyForm::CompeleteTransfer);

		  }
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

	private: System::Windows::Forms::ColumnHeader^ RowIndex;
	private: System::Windows::Forms::ColumnHeader^ Name;
	private: System::Windows::Forms::ColumnHeader^ Tenasferd;
	private: System::Windows::Forms::ColumnHeader^ Type;
	private: System::Windows::Forms::ColumnHeader^ Time;
	private: System::Windows::Forms::ColumnHeader^ Date;
	private: System::Windows::Forms::ProgressBar^ PBTreansfered;
	private: System::Windows::Forms::ComboBox^ Clients;
	private: System::Windows::Forms::TextBox^ Port;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ IP;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ BTNStart;
	private: System::Windows::Forms::Button^ BTNDonwload;


	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ServerMode;
	private: System::Windows::Forms::ToolStripMenuItem^ ClientMode;
	private: System::Windows::Forms::ToolStripMenuItem^ dataModeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ messageToolStripMenuItem;
	private: System::Windows::Forms::ListView^ QueueList;
	private: System::Windows::Forms::ColumnHeader^ ID;

	private: System::Windows::Forms::ColumnHeader^ FileName;
	private: System::Windows::Forms::ColumnHeader^ FileExtention;
	private: System::Windows::Forms::ColumnHeader^ Condition;

	private: System::Windows::Forms::ColumnHeader^ DateTime;
	private: System::Windows::Forms::ColumnHeader^ QueueType;
	private: System::Windows::Forms::ToolStripMenuItem^ uploadToolStripMenuItem;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->RowIndex = (gcnew System::Windows::Forms::ColumnHeader());
			this->Name = (gcnew System::Windows::Forms::ColumnHeader());
			this->Tenasferd = (gcnew System::Windows::Forms::ColumnHeader());
			this->Type = (gcnew System::Windows::Forms::ColumnHeader());
			this->Time = (gcnew System::Windows::Forms::ColumnHeader());
			this->Date = (gcnew System::Windows::Forms::ColumnHeader());
			this->PBTreansfered = (gcnew System::Windows::Forms::ProgressBar());
			this->Clients = (gcnew System::Windows::Forms::ComboBox());
			this->Port = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->IP = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->BTNStart = (gcnew System::Windows::Forms::Button());
			this->BTNDonwload = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ServerMode = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ClientMode = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dataModeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->fileToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->uploadToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->messageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->QueueList = (gcnew System::Windows::Forms::ListView());
			this->ID = (gcnew System::Windows::Forms::ColumnHeader());
			this->FileName = (gcnew System::Windows::Forms::ColumnHeader());
			this->FileExtention = (gcnew System::Windows::Forms::ColumnHeader());
			this->Condition = (gcnew System::Windows::Forms::ColumnHeader());
			this->DateTime = (gcnew System::Windows::Forms::ColumnHeader());
			this->QueueType = (gcnew System::Windows::Forms::ColumnHeader());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// RowIndex
			// 
			this->RowIndex->Text = L"Index";
			this->RowIndex->Width = 42;
			// 
			// Name
			// 
			this->Name->Text = L"File Name";
			this->Name->Width = 118;
			// 
			// Tenasferd
			// 
			this->Tenasferd->Text = L"Tenasferd";
			this->Tenasferd->Width = 66;
			// 
			// Type
			// 
			this->Type->Text = L"Type";
			// 
			// Time
			// 
			this->Time->Text = L"Time";
			this->Time->Width = 80;
			// 
			// Date
			// 
			this->Date->Text = L"Date";
			this->Date->Width = 104;
			// 
			// PBTreansfered
			// 
			this->PBTreansfered->Location = System::Drawing::Point(12, 249);
			this->PBTreansfered->Name = L"PBTreansfered";
			this->PBTreansfered->Size = System::Drawing::Size(419, 23);
			this->PBTreansfered->TabIndex = 17;
			// 
			// Clients
			// 
			this->Clients->FormattingEnabled = true;
			this->Clients->Location = System::Drawing::Point(296, 32);
			this->Clients->Name = L"Clients";
			this->Clients->Size = System::Drawing::Size(121, 21);
			this->Clients->TabIndex = 16;
			this->Clients->Text = L"Client";
			// 
			// Port
			// 
			this->Port->Location = System::Drawing::Point(175, 32);
			this->Port->Name = L"Port";
			this->Port->Size = System::Drawing::Size(100, 20);
			this->Port->TabIndex = 15;
			this->Port->Text = L"7071";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(143, 36);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(26, 13);
			this->label2->TabIndex = 14;
			this->label2->Text = L"Port";
			// 
			// IP
			// 
			this->IP->Location = System::Drawing::Point(43, 32);
			this->IP->Name = L"IP";
			this->IP->Size = System::Drawing::Size(94, 20);
			this->IP->TabIndex = 13;
			this->IP->Text = L"127.0.0.1";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(20, 36);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(17, 13);
			this->label1->TabIndex = 12;
			this->label1->Text = L"IP";
			// 
			// BTNStart
			// 
			this->BTNStart->Location = System::Drawing::Point(437, 31);
			this->BTNStart->Name = L"BTNStart";
			this->BTNStart->Size = System::Drawing::Size(75, 23);
			this->BTNStart->TabIndex = 10;
			this->BTNStart->Text = L"Start";
			this->BTNStart->UseVisualStyleBackColor = true;
			this->BTNStart->Click += gcnew System::EventHandler(this, &MyForm::BTNStart_Click);
			// 
			// BTNDonwload
			// 
			this->BTNDonwload->Enabled = false;
			this->BTNDonwload->Location = System::Drawing::Point(437, 249);
			this->BTNDonwload->Name = L"BTNDonwload";
			this->BTNDonwload->Size = System::Drawing::Size(75, 23);
			this->BTNDonwload->TabIndex = 11;
			this->BTNDonwload->Text = L"Download";
			this->BTNDonwload->UseVisualStyleBackColor = true;
			this->BTNDonwload->Click += gcnew System::EventHandler(this, &MyForm::BTNDonwload_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fileToolStripMenuItem,
					this->dataModeToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(523, 24);
			this->menuStrip1->TabIndex = 18;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->ServerMode,
					this->ClientMode
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(50, 20);
			this->fileToolStripMenuItem->Text = L"Mode";
			// 
			// ServerMode
			// 
			this->ServerMode->Checked = true;
			this->ServerMode->CheckState = System::Windows::Forms::CheckState::Checked;
			this->ServerMode->Name = L"ServerMode";
			this->ServerMode->Size = System::Drawing::Size(106, 22);
			this->ServerMode->Text = L"Server";
			this->ServerMode->Click += gcnew System::EventHandler(this, &MyForm::ServerMode_Click);
			// 
			// ClientMode
			// 
			this->ClientMode->Name = L"ClientMode";
			this->ClientMode->Size = System::Drawing::Size(106, 22);
			this->ClientMode->Text = L"Client";
			this->ClientMode->Click += gcnew System::EventHandler(this, &MyForm::ClientMode_Click);
			// 
			// dataModeToolStripMenuItem
			// 
			this->dataModeToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fileToolStripMenuItem1,
					this->messageToolStripMenuItem
			});
			this->dataModeToolStripMenuItem->Name = L"dataModeToolStripMenuItem";
			this->dataModeToolStripMenuItem->Size = System::Drawing::Size(77, 20);
			this->dataModeToolStripMenuItem->Text = L"Data Mode";
			// 
			// fileToolStripMenuItem1
			// 
			this->fileToolStripMenuItem1->Checked = true;
			this->fileToolStripMenuItem1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->fileToolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->uploadToolStripMenuItem });
			this->fileToolStripMenuItem1->Name = L"fileToolStripMenuItem1";
			this->fileToolStripMenuItem1->Size = System::Drawing::Size(120, 22);
			this->fileToolStripMenuItem1->Text = L"File";
			// 
			// uploadToolStripMenuItem
			// 
			this->uploadToolStripMenuItem->Name = L"uploadToolStripMenuItem";
			this->uploadToolStripMenuItem->Size = System::Drawing::Size(112, 22);
			this->uploadToolStripMenuItem->Text = L"Upload";
			this->uploadToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::uploadToolStripMenuItem_Click);
			// 
			// messageToolStripMenuItem
			// 
			this->messageToolStripMenuItem->Enabled = false;
			this->messageToolStripMenuItem->Name = L"messageToolStripMenuItem";
			this->messageToolStripMenuItem->Size = System::Drawing::Size(120, 22);
			this->messageToolStripMenuItem->Text = L"Message";
			// 
			// QueueList
			// 
			this->QueueList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(6) {
				this->ID, this->FileName,
					this->FileExtention, this->Condition, this->DateTime, this->QueueType
			});
			this->QueueList->HideSelection = false;
			this->QueueList->Location = System::Drawing::Point(12, 71);
			this->QueueList->Name = L"QueueList";
			this->QueueList->Size = System::Drawing::Size(500, 172);
			this->QueueList->TabIndex = 9;
			this->QueueList->UseCompatibleStateImageBehavior = false;
			this->QueueList->View = System::Windows::Forms::View::Details;
			this->QueueList->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::QueueList_SelectedIndexChanged);
			// 
			// ID
			// 
			this->ID->Text = L"ID";
			this->ID->Width = 41;
			// 
			// FileName
			// 
			this->FileName->Text = L"Name";
			this->FileName->Width = 96;
			// 
			// FileExtention
			// 
			this->FileExtention->Text = L"Extention";
			this->FileExtention->Width = 70;
			// 
			// Condition
			// 
			this->Condition->Text = L"Condition";
			this->Condition->Width = 88;
			// 
			// DateTime
			// 
			this->DateTime->Text = L"Date and Time";
			this->DateTime->Width = 106;
			// 
			// QueueType
			// 
			this->QueueType->Text = L"QueueType";
			this->QueueType->Width = 82;
			// 
			// MyForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Inherit;
			this->AutoScroll = true;
			this->ClientSize = System::Drawing::Size(523, 284);
			this->Controls->Add(this->IP);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->QueueList);
			this->Controls->Add(this->BTNDonwload);
			this->Controls->Add(this->PBTreansfered);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->BTNStart);
			this->Controls->Add(this->Port);
			this->Controls->Add(this->Clients);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->HelpButton = true;
			this->MaximizeBox = false;
			this->Text = L"Server";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		std::string to_stirng(String^ str)
		{
			msclr::interop::marshal_context contex;
			return contex.marshal_as<std::string>(str);
		}
		void AddClient(String^ Username , bool flag)
		{
			if (flag)
			{
				if (this->InvokeRequired)
				{
					this->Invoke(Event_ADDCLIENT, Username, flag);
					return;
				}
				Clients->Items->Add(Username);
			}
			else
			{
				if (this->InvokeRequired)
					this->Invoke(Event_ADDCLIENT, Username, flag);
				Clients->Items->Remove(Username);
			}
			
				
		}
		void ChangeClient(std::string username , bool flag)
		{
			AddClient(gcnew String(username.c_str()) , flag);
		}
		void AddNewQueue(array<String^>^ row)
		{
			if (this->InvokeRequired)
			{
				this->Invoke(Event_ADDQUEUE, gcnew array<Object^> { row });
				return;
			}
			ListViewItem^ item = gcnew ListViewItem(row);
			QueueList->Items->Add(item);
		}
		void NewQueueRow(int Queueid , String^ Name , String^ Extention)
		{
			array<String^>^ row = { Queueid.ToString() , Name , Extention , "0" , DateTime::Now.ToString() , "Upload" };
			AddNewQueue(row);
		}
		void NewQueueRow(int Queueid, std::string Name, std::string Extention)
		{
			array<String^>^ row = { Queueid.ToString() , gcnew String(Name.c_str()) , gcnew String(Extention.c_str()) , "0" , DateTime::Now.ToString() , "Download" };
			Event_ADDQUEUE(row);
		}
		void CompeleteTransfer(int Queueid)
		{
			if (this->InvokeRequired)
			{
				this->Invoke(Event_Compelete, Queueid);
				return;
			}
			IsTransfer = false;
			for each (ListViewItem^ var in QueueList->Items)
			{
				if (var->SubItems[0]->Text == Queueid.ToString())
					var->SubItems[3]->Text = "1";
			}
		}
private: System::Void ClientMode_Click(System::Object^ sender, System::EventArgs^ e) {
	ServerMode->Checked = false;
	ClientMode->Checked = true;
	Clients->Visible = false;
	BTNStart->Text = "Connect";
}
private: System::Void ServerMode_Click(System::Object^ sender, System::EventArgs^ e) {
	ServerMode->Checked = true;
	ClientMode->Checked = false;
	Clients->Visible = true;
	BTNStart->Text = "Start";
}
	   void StartServer()
	   {
		   std::string ip = to_stirng(IP->Text);
		   int port = Convert::ToInt32(Port->Text);
		   IsRunning = true;
		   Startup(ip, port, Event_UIChangeProgress, Event_UINewClient, Event_UINewRecieve);
	   }
private: System::Void uploadToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	try
	{
		if (IsRunning && !IsTransfer)
		{
			OpenFileDialog^ ofd = gcnew OpenFileDialog();
			ofd->Multiselect = false;
			ofd->CheckFileExists = true;
			ofd->CheckPathExists = true;
			ofd->Title = "Uplaod File";
			if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				try
				{
					std::string path = to_stirng(ofd->FileName);
					int queueid = SendFile(path , to_stirng(Clients->SelectedItem->ToString()));
					IsTransfer = true;
					NewQueueRow(queueid , Path::GetFileNameWithoutExtension(ofd->FileName) , Path::GetExtension(ofd->FileName));
				}
				catch (const std::exception& ex)
				{
					throw gcnew Exception(gcnew String(ex.what()));
				}

			}
		}
	}
	catch (Exception^ ex)
	{
		MessageBox::Show(ex->Message);
	}
}
	   
private: System::Void BTNStart_Click(System::Object^ sender, System::EventArgs^ e) {
	Thread^ thread = gcnew Thread(gcnew ThreadStart(this , &MyForm::StartServer));
	thread->Start();
	BTNStart->Enabled = false;
}
private: System::Void QueueList_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {	
	if ((((ListView^)sender)->SelectedItems->Count == 1) && IsRunning && !IsTransfer)
	{
		ListViewItem^ item = ((ListView^)sender)->SelectedItems[0];
		if (item->SubItems[5]->Text == "Download" && item->SubItems[3]->Text == "0")
		{
			BTNDonwload->Enabled = true;
		}
		else
			BTNDonwload->Enabled = false;
	}
	else
		BTNDonwload->Enabled = false;
}
	   void ChangeProgress(int queuid , int value)
	   {
		   if (this->InvokeRequired)
			   this->Invoke(Event_Progress , queuid , value);
		   PBTreansfered->Value = value;
		   if (PBTreansfered->Value == 100)
			   CompeleteTransfer(queuid);

	   }
private: System::Void BTNDonwload_Click(System::Object^ sender, System::EventArgs^ e) {
	BTNDonwload->Enabled = false;
	int queueid = Convert::ToInt32(QueueList->SelectedItems[0]->SubItems[0]->Text);
	StartDownload(queueid);
}
};
}
