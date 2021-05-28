#include <Windows.h>
#include <atlstr.h>
#include "Imge.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include "Modules.h"
#include "Hu_Moments.h"
#include "HelperCodes.h"
#pragma once

namespace Form_Empty
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)delete components;
		}
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ readImageToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::ComponentModel::IContainer^ components;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		EXP_OBJECT* exp = new EXP_OBJECT[50];

		std::string *stringList = new std::string[50];
		BYTE* Buffer;
		int* histogramDatas;
		int Width, Height;
		long Size;
		int itemSize;
		struct OBJECT* object;
		int k;
		BYTE* binaryImage;
		BYTE* intensityImage;
		BYTE* taggedArray;
		int index;
		int objIndex = 0;
		int objIndex2;
		int expObjectSize;

	private: System::Windows::Forms::OpenFileDialog^ openFileDialog2;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	private: System::Windows::Forms::Button^ HuMomentsButton;
	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	private: System::Windows::Forms::Button^ convertToIntensityButton;
	private: System::Windows::Forms::Button^ ObjectDetectionButton;
	private: System::Windows::Forms::Button^ HistogramButton;
	private: System::Windows::Forms::Button^ Reverse;
	private: System::Windows::Forms::ListBox^ listBox2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ AgirlikMerkeziButton;
	private: System::Windows::Forms::Button^ ErosionButton;

	private: System::Windows::Forms::Button^ DilationButton;
	private: System::Windows::Forms::Button^ learnButton;
	private: System::Windows::Forms::ListBox^ listBox3;
	private: System::Windows::Forms::Button^ ShowObjectsButton;
	private: System::Windows::Forms::ListBox^ listBox4;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Button^ SaveButton;

	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label3;

	private: System::Windows::Forms::Label^ label5;



	private: System::Windows::Forms::Button^ ConvertToBinaryButton;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Required method for Designer support - do not modify
		   /// the contents of this method with the code editor.
		   /// </summary>
		   void ShowIntensity(unsigned char* img, int w, int h, PictureBox^ pictureBox)
		   {
			   Bitmap^ surface = gcnew Bitmap(pictureBox->Width, pictureBox->Height);
			   pictureBox->Image = surface;
			   Color c;
			   int temp;
			   for (int row = 0; row < h; row++)
				   for (int column = 0; column < w; column++) {

					   temp = row * w + column;
					   c = Color::FromArgb(img[temp], img[temp], img[temp]);
					   surface->SetPixel(column, row, c);
				   }

		   }
		   void MarshalString(String^ s, std::string& os) {
			   using namespace Runtime::InteropServices;
			   const char* chars =
				   (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			   os = chars;
			   Marshal::FreeHGlobal(IntPtr((void*)chars));
		   }
		   void InitializeComponent(void)
		   {
			   System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			   System::Windows::Forms::DataVisualization::Charting::Legend^ legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			   this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			   this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->readImageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			   this->openFileDialog2 = (gcnew System::Windows::Forms::OpenFileDialog());
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			   this->HuMomentsButton = (gcnew System::Windows::Forms::Button());
			   this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			   this->convertToIntensityButton = (gcnew System::Windows::Forms::Button());
			   this->ObjectDetectionButton = (gcnew System::Windows::Forms::Button());
			   this->HistogramButton = (gcnew System::Windows::Forms::Button());
			   this->ConvertToBinaryButton = (gcnew System::Windows::Forms::Button());
			   this->Reverse = (gcnew System::Windows::Forms::Button());
			   this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->AgirlikMerkeziButton = (gcnew System::Windows::Forms::Button());
			   this->ErosionButton = (gcnew System::Windows::Forms::Button());
			   this->DilationButton = (gcnew System::Windows::Forms::Button());
			   this->learnButton = (gcnew System::Windows::Forms::Button());
			   this->listBox3 = (gcnew System::Windows::Forms::ListBox());
			   this->ShowObjectsButton = (gcnew System::Windows::Forms::Button());
			   this->listBox4 = (gcnew System::Windows::Forms::ListBox());
			   this->panel1 = (gcnew System::Windows::Forms::Panel());
			   this->SaveButton = (gcnew System::Windows::Forms::Button());
			   this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->label5 = (gcnew System::Windows::Forms::Label());
			   this->menuStrip1->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			   this->panel1->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // menuStrip1
			   // 
			   this->menuStrip1->GripMargin = System::Windows::Forms::Padding(2, 2, 0, 2);
			   this->menuStrip1->ImageScalingSize = System::Drawing::Size(22, 22);
			   this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			   this->menuStrip1->Location = System::Drawing::Point(0, 0);
			   this->menuStrip1->Name = L"menuStrip1";
			   this->menuStrip1->Size = System::Drawing::Size(1924, 31);
			   this->menuStrip1->TabIndex = 0;
			   this->menuStrip1->Text = L"menuStrip1";
			   // 
			   // fileToolStripMenuItem
			   // 
			   this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->readImageToolStripMenuItem });
			   this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			   this->fileToolStripMenuItem->Size = System::Drawing::Size(51, 27);
			   this->fileToolStripMenuItem->Text = L"File";
			   // 
			   // readImageToolStripMenuItem
			   // 
			   this->readImageToolStripMenuItem->Name = L"readImageToolStripMenuItem";
			   this->readImageToolStripMenuItem->Size = System::Drawing::Size(197, 30);
			   this->readImageToolStripMenuItem->Text = L"Read_Image";
			   this->readImageToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::readImageToolStripMenuItem_Click);
			   // 
			   // openFileDialog1
			   // 
			   this->openFileDialog1->FileName = L"openFileDialog1";
			   // 
			   // openFileDialog2
			   // 
			   this->openFileDialog2->FileName = L"openFileDialog2";
			   // 
			   // pictureBox1
			   // 
			   this->pictureBox1->Location = System::Drawing::Point(13, 116);
			   this->pictureBox1->Name = L"pictureBox1";
			   this->pictureBox1->Size = System::Drawing::Size(749, 805);
			   this->pictureBox1->TabIndex = 1;
			   this->pictureBox1->TabStop = false;
			   // 
			   // chart1
			   // 
			   this->chart1->BackColor = System::Drawing::SystemColors::Window;
			   chartArea2->Name = L"ChartArea1";
			   this->chart1->ChartAreas->Add(chartArea2);
			   legend2->Name = L"Legend1";
			   this->chart1->Legends->Add(legend2);
			   this->chart1->Location = System::Drawing::Point(786, 69);
			   this->chart1->Name = L"chart1";
			   this->chart1->Size = System::Drawing::Size(423, 248);
			   this->chart1->TabIndex = 3;
			   this->chart1->Text = L"chart1";
			   this->chart1->Visible = false;
			   // 
			   // HuMomentsButton
			   // 
			   this->HuMomentsButton->Location = System::Drawing::Point(934, 572);
			   this->HuMomentsButton->Name = L"HuMomentsButton";
			   this->HuMomentsButton->Size = System::Drawing::Size(124, 34);
			   this->HuMomentsButton->TabIndex = 7;
			   this->HuMomentsButton->Text = L"Hu Moments";
			   this->HuMomentsButton->UseVisualStyleBackColor = true;
			   this->HuMomentsButton->Visible = false;
			   this->HuMomentsButton->Click += gcnew System::EventHandler(this, &MyForm::huMoments_Click);
			   // 
			   // listBox1
			   // 
			   this->listBox1->FormattingEnabled = true;
			   this->listBox1->ItemHeight = 16;
			   this->listBox1->Location = System::Drawing::Point(786, 351);
			   this->listBox1->Name = L"listBox1";
			   this->listBox1->ScrollAlwaysVisible = true;
			   this->listBox1->Size = System::Drawing::Size(123, 196);
			   this->listBox1->TabIndex = 8;
			   this->listBox1->Tag = L"";
			   this->listBox1->Visible = false;
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Location = System::Drawing::Point(783, 332);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(69, 16);
			   this->label1->TabIndex = 9;
			   this->label1->Text = L"Trasholds";
			   this->label1->Visible = false;
			   // 
			   // pictureBox3
			   // 
			   this->pictureBox3->Location = System::Drawing::Point(1138, 351);
			   this->pictureBox3->Name = L"pictureBox3";
			   this->pictureBox3->Size = System::Drawing::Size(749, 777);
			   this->pictureBox3->TabIndex = 10;
			   this->pictureBox3->TabStop = false;
			   // 
			   // convertToIntensityButton
			   // 
			   this->convertToIntensityButton->Location = System::Drawing::Point(13, 34);
			   this->convertToIntensityButton->Name = L"convertToIntensityButton";
			   this->convertToIntensityButton->Size = System::Drawing::Size(197, 23);
			   this->convertToIntensityButton->TabIndex = 11;
			   this->convertToIntensityButton->Text = L"Convert to Intensity";
			   this->convertToIntensityButton->UseVisualStyleBackColor = true;
			   this->convertToIntensityButton->Visible = false;
			   this->convertToIntensityButton->Click += gcnew System::EventHandler(this, &MyForm::convertToIntensityButton_Click);
			   // 
			   // ObjectDetectionButton
			   // 
			   this->ObjectDetectionButton->Location = System::Drawing::Point(547, 34);
			   this->ObjectDetectionButton->Name = L"ObjectDetectionButton";
			   this->ObjectDetectionButton->Size = System::Drawing::Size(165, 23);
			   this->ObjectDetectionButton->TabIndex = 12;
			   this->ObjectDetectionButton->Text = L"Object Detection";
			   this->ObjectDetectionButton->UseVisualStyleBackColor = true;
			   this->ObjectDetectionButton->Visible = false;
			   this->ObjectDetectionButton->Click += gcnew System::EventHandler(this, &MyForm::ObjectDetectionButton_Click);
			   // 
			   // HistogramButton
			   // 
			   this->HistogramButton->Location = System::Drawing::Point(242, 34);
			   this->HistogramButton->Name = L"HistogramButton";
			   this->HistogramButton->Size = System::Drawing::Size(86, 23);
			   this->HistogramButton->TabIndex = 13;
			   this->HistogramButton->Text = L"Histogram";
			   this->HistogramButton->UseVisualStyleBackColor = true;
			   this->HistogramButton->Visible = false;
			   this->HistogramButton->Click += gcnew System::EventHandler(this, &MyForm::HistogramButton_Click);
			   // 
			   // ConvertToBinaryButton
			   // 
			   this->ConvertToBinaryButton->Location = System::Drawing::Point(371, 34);
			   this->ConvertToBinaryButton->Name = L"ConvertToBinaryButton";
			   this->ConvertToBinaryButton->Size = System::Drawing::Size(135, 23);
			   this->ConvertToBinaryButton->TabIndex = 14;
			   this->ConvertToBinaryButton->Text = L"Convert to Binary";
			   this->ConvertToBinaryButton->UseVisualStyleBackColor = true;
			   this->ConvertToBinaryButton->Visible = false;
			   this->ConvertToBinaryButton->Click += gcnew System::EventHandler(this, &MyForm::ConvertToBinaryButton_Click);
			   // 
			   // Reverse
			   // 
			   this->Reverse->Location = System::Drawing::Point(736, 34);
			   this->Reverse->Name = L"Reverse";
			   this->Reverse->Size = System::Drawing::Size(122, 23);
			   this->Reverse->TabIndex = 15;
			   this->Reverse->Text = L"Reverse";
			   this->Reverse->UseVisualStyleBackColor = true;
			   this->Reverse->Visible = false;
			   this->Reverse->Click += gcnew System::EventHandler(this, &MyForm::ReverseButton_Click);
			   // 
			   // listBox2
			   // 
			   this->listBox2->FormattingEnabled = true;
			   this->listBox2->ItemHeight = 16;
			   this->listBox2->Location = System::Drawing::Point(924, 351);
			   this->listBox2->Name = L"listBox2";
			   this->listBox2->Size = System::Drawing::Size(197, 196);
			   this->listBox2->TabIndex = 17;
			   this->listBox2->Visible = false;
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->Location = System::Drawing::Point(921, 332);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(40, 16);
			   this->label2->TabIndex = 18;
			   this->label2->Text = L"Items";
			   this->label2->Visible = false;
			   // 
			   // AgirlikMerkeziButton
			   // 
			   this->AgirlikMerkeziButton->Location = System::Drawing::Point(898, 35);
			   this->AgirlikMerkeziButton->Name = L"AgirlikMerkeziButton";
			   this->AgirlikMerkeziButton->Size = System::Drawing::Size(181, 23);
			   this->AgirlikMerkeziButton->TabIndex = 21;
			   this->AgirlikMerkeziButton->Text = L"aðýrlýk merkezi";
			   this->AgirlikMerkeziButton->UseVisualStyleBackColor = true;
			   this->AgirlikMerkeziButton->Click += gcnew System::EventHandler(this, &MyForm::AgirlikMerkeziButton_Click);
			   // 
			   // ErosionButton
			   // 
			   this->ErosionButton->Location = System::Drawing::Point(767, 582);
			   this->ErosionButton->Name = L"ErosionButton";
			   this->ErosionButton->Size = System::Drawing::Size(114, 23);
			   this->ErosionButton->TabIndex = 22;
			   this->ErosionButton->Text = L"erosion";
			   this->ErosionButton->UseVisualStyleBackColor = true;
			   this->ErosionButton->Visible = false;
			   this->ErosionButton->Click += gcnew System::EventHandler(this, &MyForm::ErosionButton_Click);
			   // 
			   // DilationButton
			   // 
			   this->DilationButton->Location = System::Drawing::Point(767, 611);
			   this->DilationButton->Name = L"DilationButton";
			   this->DilationButton->Size = System::Drawing::Size(114, 23);
			   this->DilationButton->TabIndex = 24;
			   this->DilationButton->Text = L"dialtion";
			   this->DilationButton->UseVisualStyleBackColor = true;
			   this->DilationButton->Visible = false;
			   this->DilationButton->Click += gcnew System::EventHandler(this, &MyForm::DilationButton_Click);
			   // 
			   // learnButton
			   // 
			   this->learnButton->Location = System::Drawing::Point(1123, 34);
			   this->learnButton->Name = L"learnButton";
			   this->learnButton->Size = System::Drawing::Size(148, 23);
			   this->learnButton->TabIndex = 25;
			   this->learnButton->Text = L"learn";
			   this->learnButton->UseVisualStyleBackColor = true;
			   this->learnButton->Click += gcnew System::EventHandler(this, &MyForm::learnButton_Click);
			   // 
			   // listBox3
			   // 
			   this->listBox3->FormattingEnabled = true;
			   this->listBox3->ItemHeight = 16;
			   this->listBox3->Location = System::Drawing::Point(1235, 69);
			   this->listBox3->Name = L"listBox3";
			   this->listBox3->Size = System::Drawing::Size(180, 228);
			   this->listBox3->TabIndex = 26;
			   // 
			   // ShowObjectsButton
			   // 
			   this->ShowObjectsButton->Location = System::Drawing::Point(767, 640);
			   this->ShowObjectsButton->Name = L"ShowObjectsButton";
			   this->ShowObjectsButton->Size = System::Drawing::Size(114, 23);
			   this->ShowObjectsButton->TabIndex = 27;
			   this->ShowObjectsButton->Text = L"Show Objects";
			   this->ShowObjectsButton->UseVisualStyleBackColor = true;
			   this->ShowObjectsButton->Visible = false;
			   this->ShowObjectsButton->Click += gcnew System::EventHandler(this, &MyForm::ShowObjectsButton_Click);
			   // 
			   // listBox4
			   // 
			   this->listBox4->FormattingEnabled = true;
			   this->listBox4->ItemHeight = 16;
			   this->listBox4->Location = System::Drawing::Point(767, 669);
			   this->listBox4->Name = L"listBox4";
			   this->listBox4->Size = System::Drawing::Size(265, 212);
			   this->listBox4->TabIndex = 28;
			   // 
			   // panel1
			   // 
			   this->panel1->BackColor = System::Drawing::Color::SpringGreen;
			   this->panel1->Controls->Add(this->SaveButton);
			   this->panel1->Controls->Add(this->textBox1);
			   this->panel1->Controls->Add(this->label3);
			   this->panel1->Location = System::Drawing::Point(604, 202);
			   this->panel1->Name = L"panel1";
			   this->panel1->Size = System::Drawing::Size(371, 155);
			   this->panel1->TabIndex = 29;
			   this->panel1->Visible = false;
			   // 
			   // SaveButton
			   // 
			   this->SaveButton->Location = System::Drawing::Point(150, 87);
			   this->SaveButton->Name = L"SaveButton";
			   this->SaveButton->Size = System::Drawing::Size(75, 23);
			   this->SaveButton->TabIndex = 2;
			   this->SaveButton->Text = L"SAVE";
			   this->SaveButton->UseVisualStyleBackColor = true;
			   this->SaveButton->Click += gcnew System::EventHandler(this, &MyForm::SaveButton_Click);
			   // 
			   // textBox1
			   // 
			   this->textBox1->Location = System::Drawing::Point(150, 49);
			   this->textBox1->Name = L"textBox1";
			   this->textBox1->Size = System::Drawing::Size(166, 22);
			   this->textBox1->TabIndex = 1;
			   // 
			   // label3
			   // 
			   this->label3->AutoSize = true;
			   this->label3->Location = System::Drawing::Point(57, 49);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(87, 16);
			   this->label3->TabIndex = 0;
			   this->label3->Text = L"Object Name";
			   // 
			   // label5
			   // 
			   this->label5->AutoSize = true;
			   this->label5->Location = System::Drawing::Point(13, 94);
			   this->label5->Name = L"label5";
			   this->label5->Size = System::Drawing::Size(45, 16);
			   this->label5->TabIndex = 31;
			   this->label5->Text = L"label5";
			   this->label5->Visible = false;
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1924, 1052);
			   this->Controls->Add(this->label5);
			   this->Controls->Add(this->panel1);
			   this->Controls->Add(this->listBox4);
			   this->Controls->Add(this->ShowObjectsButton);
			   this->Controls->Add(this->listBox3);
			   this->Controls->Add(this->learnButton);
			   this->Controls->Add(this->DilationButton);
			   this->Controls->Add(this->ErosionButton);
			   this->Controls->Add(this->AgirlikMerkeziButton);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->listBox2);
			   this->Controls->Add(this->Reverse);
			   this->Controls->Add(this->ConvertToBinaryButton);
			   this->Controls->Add(this->HistogramButton);
			   this->Controls->Add(this->ObjectDetectionButton);
			   this->Controls->Add(this->convertToIntensityButton);
			   this->Controls->Add(this->pictureBox3);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->listBox1);
			   this->Controls->Add(this->HuMomentsButton);
			   this->Controls->Add(this->chart1);
			   this->Controls->Add(this->pictureBox1);
			   this->Controls->Add(this->menuStrip1);
			   this->MainMenuStrip = this->menuStrip1;
			   this->Margin = System::Windows::Forms::Padding(4);
			   this->Name = L"MyForm";
			   this->Text = L"MyForm";
			   this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			   this->menuStrip1->ResumeLayout(false);
			   this->menuStrip1->PerformLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			   this->panel1->ResumeLayout(false);
			   this->panel1->PerformLayout();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }

#pragma endregion
	private: System::Void readImageToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
	{
		index = 0;

		chart1->Series->Clear();

		LPCTSTR input;

		CString str;

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			str = openFileDialog1->FileName;

			input = (LPCTSTR)str;

			Buffer = LoadBMP(Width, Height, Size, input);

			intensityImage = Buffer;

			pictureBox1->Width = Width;

			pictureBox1->Height = Height;

			this->pictureBox1->ImageLocation = openFileDialog1->FileName;
		}

		convertToIntensityButton->Visible = true;

		HistogramButton->Visible = true;

	}

	private: System::Void huMoments_Click(System::Object^ sender, System::EventArgs^ e)
	{

		listBox2->Items->Clear();

		struct OBJECT obj = object[index];

		myHuMoments* moments = new myHuMoments(obj.image, obj.itemWidth, obj.itemHeight);

		label2->Text = index.ToString() + ". Item";

		double* dizi = moments->getHuMoments();

		moments->logTransform();

		for (int i = 0; i < 7; i++)
			listBox2->Items->Add(dizi[i].ToString());

		ShowIntensity(obj.image, obj.itemWidth, obj.itemHeight, pictureBox3);



		index = index == itemSize - 1 ? 0 : index + 1;
	}

	private: System::Void convertToIntensityButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		intensityImage = ConvertBMPToIntensity(Buffer, Width, Height, Size);

		ShowIntensity(intensityImage, Width, Height, pictureBox1);
	}

	private: System::Void HistogramButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		histogramDatas = new int[256];

		createHistogramDatas(histogramDatas, intensityImage, Size);

		chart1->Visible = true;

		chart1->Series->Add("abc");

		for (int i = 0; i < 256; i++)
			chart1->Series["abc"]->Points->Add(histogramDatas[i]);

		ConvertToBinaryButton->Visible = true;
	}

	private: System::Void ConvertToBinaryButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		HuMomentsButton->Visible = true;

		listBox2->Visible = true;

		int k = 2;

		struct KVALUES* KValues = KMeans(histogramDatas, Size, k);

		binaryImage = new BYTE[Size];

		for (int i = 0; i < Size; i++) 
		{
			int kvalues_index = Closest(intensityImage[i], KValues, k);
		
			binaryImage[i] = KValues[kvalues_index].brightnessAssignment;
		}

		listBox1->Items->Clear();

		for (int i = 0; i < k; i++)
			listBox1->Items->Add("K" + (i + 1).ToString() + ": " + KValues[i].kValue.ToString());

		label1->Visible = true;

		listBox1->Visible = true;

		ShowIntensity(binaryImage, Width, Height, pictureBox1);

		free(KValues);

		ObjectDetectionButton->Visible = true;

		Reverse->Visible = true;

		ErosionButton->Visible = true;

		DilationButton->Visible = true;
	}

	private: System::Void ObjectDetectionButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		listBox4->Items->Clear();

		BYTE* labeledImage = Labeling(binaryImage, Size, Width, Height, itemSize);

		BYTE* temp = new BYTE[Width * Height];

		for (int i = 0; i < Width * Height; i++)
		{
			if (labeledImage[i] != 0)
			{
				temp[i] = labeledImage[i] + 50;
			}
			else temp[i] = 0;
		}
		ShowIntensity(temp, Width, Height, pictureBox1);
		object = ObjectDetection(labeledImage, Width, Size, Height, itemSize);

		for (int i = 0; i < itemSize; i++)
		{
			listBox4->Items->Add((i + 1) + ". Object maxRow: " + object[i].maxRowValue);
			listBox4->Items->Add((i + 1) + ". Object minRow: " + object[i].minRowValue);
			listBox4->Items->Add((i + 1) + ". Object maxCol: " + object[i].maxColumnValue);
			listBox4->Items->Add((i + 1) + ". Object minCol: " + object[i].minColumnValue);

			listBox4->Items->Add(" ");
		}

		HuMomentsButton->Visible = true;

		label2->Visible = true;

		listBox2->Visible = true;

		ErosionButton->Visible = false;

		DilationButton->Visible = false;

		free(intensityImage);
		free(histogramDatas);
		free(temp);
	}

	private: System::Void ReverseButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		index = 0;
		for (int i = 0; i < Size; i++) binaryImage[i] = binaryImage[i] == 0 ? 255 : 0;

		ShowIntensity(binaryImage, Width, Height, pictureBox1);
	}

	private: System::Void AgirlikMerkeziButton_Click(System::Object^ sender, System::EventArgs^ e)
	{

		listBox2->Items->Clear();

		double* arraySum = Training(itemSize, objIndex, object, exp);

		for (int i = 0; i < 7; i++) 
			listBox2->Items->Add(arraySum[i].ToString());
		
		
		panel1->Visible = true;

	}

	private: System::Void ErosionButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		struct MASK mask;

		mask.height = 3;
		mask.width = 3;

		Erosion(binaryImage, Width, Height, mask);

		ShowIntensity(binaryImage, Width, Height, pictureBox1);
	}

	private: System::Void DilationButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		struct MASK mask;

		mask.height = 3;
		mask.width = 3;

		Dilation(binaryImage, Width, Height, mask);

		ShowIntensity(binaryImage, Width, Height, pictureBox1);
	}

	private: System::Void learnButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		listBox3->Items->Clear();

		expObjectSize = objIndex;

		Matching(itemSize, object, expObjectSize, exp);
		
		for (int i = 0; i < itemSize; i++)
		{
			int objName = object[i].objectName;

			String^ newSystemString = gcnew String(stringList[objName].c_str());

			listBox3->Items->Add("Object-" + i + ": " + newSystemString);
		}

		ShowObjectsButton->Visible = true;
	}

	private: System::Void ShowObjectsButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		BYTE* image = ShowObjects(object, exp[objIndex2], Width, Height, itemSize);

		ShowIntensity(image, Width, Height, pictureBox1);

		label5->Visible = true;

		String^ newSystemString = gcnew String(stringList[objIndex2].c_str());

		label5->Text = newSystemString;



		objIndex2 = objIndex2 == expObjectSize - 1 ? 0 : objIndex2 + 1;
	}

	private: System::Void SaveButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		String^ c = gcnew String(textBox1->Text);

		MarshalString(c, stringList[objIndex]);

		objIndex++;

		panel1->Visible = false;
	}
private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
}
};
}