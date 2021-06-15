#pragma once
#include <Windows.h>
#include <cstring>
#include <string.h>
#include "imge.h"
#include <string>
#include <tchar.h>
#include <atlstr.h>
#include <iostream>

namespace Form_Empty {

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
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ readImageToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		BYTE* Buffer, * Raw_Intensity;
		int* gradiantImage;

		int* colImage;
		int* rowImage;
		int Width, Height;
		long Size;
		int* angles;
		int* nonMaskSup;
		int* bitArr = new int[1020]{0};
		int otsuTrh;
		BYTE* circle;
		BYTE* line;

	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::ToolStripMenuItem^ grayImageToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ cannyToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ gradientToolStripMenuItem;
	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::Windows::Forms::ToolStripMenuItem^ caneToolStripMenuItem;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;


	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::ToolStripMenuItem^ houghTransformToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ lineToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ circleToolStripMenuItem;


		   System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Required method for Designer support - do not modify
		   /// the contents of this method with the code editor.
		   /// </summary>
		   /// 
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
		   void ShowIntensity(int* img, int w, int h, PictureBox^ pictureBox)
		   {
			   listBox1->Items->Clear();

			   int max = 0, min = 1020;
			   for (int i = 0; i < h; i++)
				   for (int j = 0; j < w; j++)
				   {
					   max = img[i * w + j] > max ? img[i * w + j] : max;
					   min = img[i * w + j] < min ? img[i * w + j] : min;
				   }
			   listBox1->Items->Add("min: " + min + ", max: " + max);
			   float norm = 255.0 / (max - min);
			   Bitmap^ surface = gcnew Bitmap(pictureBox->Width, pictureBox->Height);
			   pictureBox->Image = surface;
			   Color c;
			   int temp;
			   for (int row = 0; row < h; row++)
				   for (int column = 0; column < w; column++) {

					   temp = (row * w + column);
					   c = Color::FromArgb(img[temp] * norm, img[temp] * norm, img[temp] * norm);
					   surface->SetPixel(column, row, c);
				   }

		   }
		   
		   void InitializeComponent(void)
		   {
			   System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			   System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			   System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			   this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			   this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->readImageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->grayImageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->cannyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->gradientToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->caneToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->houghTransformToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->lineToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			   this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			   this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			   this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			   this->button3 = (gcnew System::Windows::Forms::Button());
			   this->circleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->menuStrip1->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // menuStrip1
			   // 
			   this->menuStrip1->GripMargin = System::Windows::Forms::Padding(2, 2, 0, 2);
			   this->menuStrip1->ImageScalingSize = System::Drawing::Size(22, 22);
			   this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				   this->fileToolStripMenuItem,
					   this->cannyToolStripMenuItem, this->houghTransformToolStripMenuItem
			   });
			   this->menuStrip1->Location = System::Drawing::Point(0, 0);
			   this->menuStrip1->Name = L"menuStrip1";
			   this->menuStrip1->Padding = System::Windows::Forms::Padding(8, 2, 0, 2);
			   this->menuStrip1->Size = System::Drawing::Size(1909, 31);
			   this->menuStrip1->TabIndex = 0;
			   this->menuStrip1->Text = L"menuStrip1";
			   // 
			   // fileToolStripMenuItem
			   // 
			   this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				   this->readImageToolStripMenuItem,
					   this->grayImageToolStripMenuItem
			   });
			   this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			   this->fileToolStripMenuItem->Size = System::Drawing::Size(51, 27);
			   this->fileToolStripMenuItem->Text = L"File";
			   // 
			   // readImageToolStripMenuItem
			   // 
			   this->readImageToolStripMenuItem->Name = L"readImageToolStripMenuItem";
			   this->readImageToolStripMenuItem->Size = System::Drawing::Size(195, 30);
			   this->readImageToolStripMenuItem->Text = L"Read Image";
			   this->readImageToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::readImageToolStripMenuItem_Click);
			   // 
			   // grayImageToolStripMenuItem
			   // 
			   this->grayImageToolStripMenuItem->Name = L"grayImageToolStripMenuItem";
			   this->grayImageToolStripMenuItem->Size = System::Drawing::Size(195, 30);
			   this->grayImageToolStripMenuItem->Text = L"Gray Image";
			   this->grayImageToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::grayImageToolStripMenuItem_Click);
			   // 
			   // cannyToolStripMenuItem
			   // 
			   this->cannyToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				   this->gradientToolStripMenuItem,
					   this->caneToolStripMenuItem
			   });
			   this->cannyToolStripMenuItem->Name = L"cannyToolStripMenuItem";
			   this->cannyToolStripMenuItem->Size = System::Drawing::Size(74, 27);
			   this->cannyToolStripMenuItem->Text = L"Canny";
			   // 
			   // gradientToolStripMenuItem
			   // 
			   this->gradientToolStripMenuItem->Name = L"gradientToolStripMenuItem";
			   this->gradientToolStripMenuItem->Size = System::Drawing::Size(170, 30);
			   this->gradientToolStripMenuItem->Text = L"Gradient";
			   this->gradientToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::gradientToolStripMenuItem_Click);
			   // 
			   // caneToolStripMenuItem
			   // 
			   this->caneToolStripMenuItem->Name = L"caneToolStripMenuItem";
			   this->caneToolStripMenuItem->Size = System::Drawing::Size(170, 30);
			   this->caneToolStripMenuItem->Text = L"Canny";
			   this->caneToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::caneToolStripMenuItem_Click);
			   // 
			   // houghTransformToolStripMenuItem
			   // 
			   this->houghTransformToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				   this->lineToolStripMenuItem,
					   this->circleToolStripMenuItem
			   });
			   this->houghTransformToolStripMenuItem->Name = L"houghTransformToolStripMenuItem";
			   this->houghTransformToolStripMenuItem->Size = System::Drawing::Size(159, 27);
			   this->houghTransformToolStripMenuItem->Text = L"Hough Transform";
			   // 
			   // lineToolStripMenuItem
			   // 
			   this->lineToolStripMenuItem->Name = L"lineToolStripMenuItem";
			   this->lineToolStripMenuItem->Size = System::Drawing::Size(252, 30);
			   this->lineToolStripMenuItem->Text = L"Line";
			   this->lineToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::lineToolStripMenuItem_Click);
			   // 
			   // pictureBox1
			   // 
			   this->pictureBox1->Location = System::Drawing::Point(16, 55);
			   this->pictureBox1->Margin = System::Windows::Forms::Padding(4);
			   this->pictureBox1->Name = L"pictureBox1";
			   this->pictureBox1->Size = System::Drawing::Size(480, 355);
			   this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			   this->pictureBox1->TabIndex = 1;
			   this->pictureBox1->TabStop = false;
			   // 
			   // openFileDialog1
			   // 
			   this->openFileDialog1->FileName = L"openFileDialog1";
			   // 
			   // pictureBox2
			   // 
			   this->pictureBox2->Location = System::Drawing::Point(699, 55);
			   this->pictureBox2->Margin = System::Windows::Forms::Padding(4);
			   this->pictureBox2->Name = L"pictureBox2";
			   this->pictureBox2->Size = System::Drawing::Size(1197, 933);
			   this->pictureBox2->TabIndex = 2;
			   this->pictureBox2->TabStop = false;
			   // 
			   // listBox1
			   // 
			   this->listBox1->FormattingEnabled = true;
			   this->listBox1->ItemHeight = 16;
			   this->listBox1->Location = System::Drawing::Point(1224, 488);
			   this->listBox1->Margin = System::Windows::Forms::Padding(4);
			   this->listBox1->Name = L"listBox1";
			   this->listBox1->Size = System::Drawing::Size(148, 308);
			   this->listBox1->TabIndex = 3;
			   // 
			   // chart1
			   // 
			   chartArea1->Name = L"ChartArea1";
			   this->chart1->ChartAreas->Add(chartArea1);
			   legend1->Name = L"Legend1";
			   this->chart1->Legends->Add(legend1);
			   this->chart1->Location = System::Drawing::Point(1224, 83);
			   this->chart1->Name = L"chart1";
			   series1->ChartArea = L"ChartArea1";
			   series1->Legend = L"Legend1";
			   series1->Name = L"Series1";
			   this->chart1->Series->Add(series1);
			   this->chart1->Size = System::Drawing::Size(598, 398);
			   this->chart1->TabIndex = 4;
			   this->chart1->Text = L"chart1";
			   // 
			   // button3
			   // 
			   this->button3->Location = System::Drawing::Point(551, 12);
			   this->button3->Name = L"button3";
			   this->button3->Size = System::Drawing::Size(141, 23);
			   this->button3->TabIndex = 7;
			   this->button3->Text = L"Gaussian Blur";
			   this->button3->UseVisualStyleBackColor = true;
			   this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			   // 
			   // circleToolStripMenuItem
			   // 
			   this->circleToolStripMenuItem->Name = L"circleToolStripMenuItem";
			   this->circleToolStripMenuItem->Size = System::Drawing::Size(252, 30);
			   this->circleToolStripMenuItem->Text = L"Circle";
			   this->circleToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::circleToolStripMenuItem_Click);
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1909, 1026);
			   this->Controls->Add(this->button3);
			   this->Controls->Add(this->chart1);
			   this->Controls->Add(this->listBox1);
			   this->Controls->Add(this->pictureBox2);
			   this->Controls->Add(this->pictureBox1);
			   this->Controls->Add(this->menuStrip1);
			   this->MainMenuStrip = this->menuStrip1;
			   this->Margin = System::Windows::Forms::Padding(4);
			   this->Name = L"MyForm";
			   this->Text = L"MyForm";
			   this->menuStrip1->ResumeLayout(false);
			   this->menuStrip1->PerformLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
	private: System::Void readImageToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		CString str;
		LPCTSTR input;
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			str = openFileDialog1->FileName;
			input = (LPCTSTR)str;
			Buffer = LoadBMP(Width, Height, Size, input);
			Raw_Intensity = Buffer;
			pictureBox1->Width = Width;
			pictureBox1->Height = Height;

			this->pictureBox1->ImageLocation = openFileDialog1->FileName;
		}
	};
	private: System::Void grayImageToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		Raw_Intensity = ConvertToIntensity(Buffer, Width, Height);
		ShowIntensity(Raw_Intensity, Width, Height, pictureBox1);

	}
	private: System::Void gradientToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		
		colImage = new int[Width * Height];
		rowImage = new int[Width * Height];

		
		gradiantImage = Gradiant(Raw_Intensity, colImage, rowImage, Width, Height);

	
		ShowIntensity(gradiantImage, Width, Height, pictureBox1);


		
	}
	private: System::Void caneToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
	{

		angles = Angles(rowImage, colImage, Width, Height);

		
		nonMaskSup = NonMaxSupprising(angles, gradiantImage, NULL, Width, Height);
		
		histogram(bitArr, nonMaskSup, Width * Height);

		

		otsuTrh = OtsuThresholding(bitArr, Width, Height);

		int tHigh = otsuTrh / 2;
		int tLow = otsuTrh / 4;

		followData(nonMaskSup, NULL, angles, Width, Height, tHigh, tLow);
		
		ShowIntensity(nonMaskSup, Width, Height, pictureBox2);
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		Raw_Intensity = GaussianFilter(Raw_Intensity, Width, Height);
		ShowIntensity(Raw_Intensity, Width, Height, pictureBox1);

	}
	private: System::Void lineToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
	{

		line = LineDetection(nonMaskSup, Width, Height, Size, Raw_Intensity);

		ShowIntensity(line, Width, Height, pictureBox1);
	}
	private: System::Void circleToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		
		circle = CircleDetection(nonMaskSup, Width, Height, Size, Raw_Intensity);
		ShowIntensity(circle, Width, Height, pictureBox1);

	}
};
};
 

