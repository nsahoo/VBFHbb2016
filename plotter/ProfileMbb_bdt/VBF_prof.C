#include <iostream>
#include <fstream>
#include <algorithm>
#include <TH1F.h>
#include <TF1.h>
#include <TTree.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLorentzVector.h"
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TFile.h"
#include "THStack.h"
#include "TROOT.h"
#include "TLatex.h"
#include "TLegend.h"
#include "RooRealVar.h"
#include "RooDataHist.h"
#include "RooStats/SPlot.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooFormulaVar.h"
#include "RooGaussian.h"
#include "RooExponential.h"
#include "RooCBShape.h"
#include "RooChebychev.h"
#include "RooBernstein.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooAddition.h"
#include "RooProduct.h"
#include "TCanvas.h"
#include "RooAbsPdf.h"
#include "RooFit.h"
#include "RooFitResult.h"
#include "RooWorkspace.h"
#include "RooConstVar.h"
#include "RooPlot.h"
#include "TPaveText.h"
#include "TVirtualPad.h"
#include "TProfile.h"


using namespace RooFit ;
using namespace std;


int main(int argc, char* argv[]){

	int type_int = atoi(argv[1]);
	
//int JECR_unc_mbb(int type_int, int type_jec){
	gROOT->ProcessLine(".x /afs/cern.ch/work/n/nchernya/setTDRStyle.C");


//	int type_int; //double  =0; single=1
	
	TString type;
	if (type_int==0) type = "_double";
	if (type_int==1) type = "_single";
	TString text_type;
	if (type_int==0) text_type = "DoubleB";
	if (type_int==1) text_type = "SingleB(High M_{jj})";
	TString jec="";

	int NCATS;
	Float_t cats[10]; 
	Float_t Nevt_up[10];
	Float_t Nevt_nom[10];
	Float_t Nevt_down[10];
	Float_t SysUnc[10];
	TString cats_names[10];
//	int NCATS_single = 0;
//	if (type_int==0) NCATS_single= 4;
	if (type_int==0) NCATS=3+1;
	else if (type_int==1) NCATS=4+1;
	if (type_int==1) {
		Float_t cats_new[10]={-1.,0.28  , 0.72  , 0.87 , 0.93    , 0.9825};
		memcpy(cats, cats_new, sizeof cats_new);
	}
	if (type_int==0) {
		Float_t cats_new[10]={-1.,0.36 ,  0.76  , 0.89  ,0.9725};
		memcpy(cats, cats_new, sizeof cats_new);
	}
	for (int i=0;i<NCATS;i++){
		TString tmp;
		tmp.Form("%1d",i);
		cats_names[i] = "CAT";
		cats_names[i].Append(tmp);
	} 
//		Float_t cats[10] = {-1.,0.12,0.44,0.57,0.6725};

	Float_t lumi = 2320.;
	Float_t xsec[2] =  {2.20,25.69};

	const int num_ss = 2;	

//	TString s_names[num_ss] = {"VBFHToBB_M-125_13TeV_powheg","GF"};
	TString s_names[num_ss] = {"vbf_jecr_v21","gf_jecr_v21"};
//	TString s_names[num_ss] = {"vbf_76"};
	TString tex_s_names[num_ss] = {"VBF, m(H) = 125 GeV", "GF, m(H) = 125 GeV"};
		

//up down variabtion loop


RooWorkspace w("w","workspace");
	char cmd[50];
	char cmd2[50];
	char cmd3[50];








	TString path="dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat/store/user/nchernya/VBFHbb2016/plotterOutput/v25/";
	TCanvas *c3 = new TCanvas();
	TFile *file_down =  TFile::Open(path+"BTagCSV_analysis"+type+"_trignone_v25_VBFbdt.root");
	TProfile *hist_mbb_reg= (TProfile*)file_down->Get("hprof_VBF_range");
//	TProfile *hist_mbb_reg= (TProfile*)file_down->Get("hprof_VBF");
	hist_mbb_reg->SetLineColor(1);
	hist_mbb_reg->SetMarkerColor(1);
	hist_mbb_reg->SetMarkerStyle(20);
	hist_mbb_reg->SetStats(kFALSE);
/////////

	TFile *file_qcd =  TFile::Open(path+"QCD_analysis"+type+"_trignone_v25_VBFbdt.root");
	TProfile *hist_mbb_reg_qcd= (TProfile*)file_qcd->Get("hprof_VBF_range");
//	TProfile *hist_mbb_reg_qcd= (TProfile*)file_qcd->Get("hprof_VBF");
	hist_mbb_reg_qcd->SetStats(kFALSE);
	hist_mbb_reg_qcd->SetLineColor(kBlue);
	hist_mbb_reg_qcd->SetMarkerColor(kBlue);
	hist_mbb_reg_qcd->SetMarkerStyle(24);
	if (type_int==1) hist_mbb_reg_qcd->Rebin(4);
	if (type_int==0) hist_mbb_reg_qcd->Rebin(4);


 	TCanvas* c_roo = new TCanvas("Fit","",800,800) ;
	TH1F *frame2 = new TH1F("frame2","",50,-1.,1.);
//	frame2->SetMinimum(0.);
	frame2->GetXaxis()->SetNdivisions(505);
	frame2->GetYaxis()->SetRangeUser(80,200);
//	frame2->GetYaxis()->SetRangeUser(80,140);
   frame2->SetStats(0);
	frame2->SetXTitle(hist_mbb_reg->GetXaxis()->GetTitle());
	frame2->SetYTitle(hist_mbb_reg->GetYaxis()->GetTitle());
	frame2->Draw();


	hist_mbb_reg->Draw("Psame");
	hist_mbb_reg_qcd->Draw("same");
	



	gPad->RedrawAxis();


	float right   = gStyle->GetPadRightMargin();
	float top = gStyle->GetPadTopMargin();
	float left =  gStyle->GetPadLeftMargin();
	float bottom = gStyle->GetPadBottomMargin();




	TPaveText pave(0.65,0.8,1.-right-top*0.5333,1.-top*1.666,"NDC");
	pave.SetTextAlign(11);
	pave.SetFillStyle(-1);
	pave.SetBorderSize(0);
	pave.SetTextFont(42);
	pave.SetTextSize(top*0.5);
	pave.SetTextColor(kBlue+1);

	sprintf(cmd,"\%s",text_type.Data())	;
	pave.AddText(cmd);

	pave.Draw("same");


	TPaveText pave22(0.2,0.8,0.4,1.-top*1.666,"NDC");
	pave22.SetTextAlign(11);
	pave22.SetFillStyle(-1);
	pave22.SetBorderSize(0);
	pave22.SetTextFont(62);
	pave22.SetTextSize(top*0.5);
//	pave22.AddText("Z-boson search");
//	pave22.Draw("same");


// CMS info
	float left2 = gStyle->GetPadLeftMargin();
	float right2 = gStyle->GetPadRightMargin();
	float top2 = gStyle->GetPadTopMargin();
	float bottom2 = gStyle->GetPadBottomMargin();




	TPaveText pCMS1(left2,1.-top2,0.4,1.,"NDC");
	pCMS1.SetTextFont(62);
	pCMS1.SetTextSize(top2*0.75);
	pCMS1.SetTextAlign(12);
	pCMS1.SetFillStyle(-1);
	pCMS1.SetBorderSize(0);
	pCMS1.AddText("CMS");
	TPaveText pCMS12(left2+0.1,1.-top2*1.1,0.6,1.,"NDC");
	pCMS12.SetTextFont(52);
	pCMS12.SetTextSize(top2*0.75);
	pCMS12.SetTextAlign(12);
	pCMS12.SetFillStyle(-1);
	pCMS12.SetBorderSize(0);
	pCMS12.AddText("Preliminary");
	TPaveText pCMS2(0.5,1.-top2,1.-right2*0.5,1.,"NDC");
	pCMS2.SetTextFont(42);
	pCMS2.SetTextSize(top2*0.75);
	pCMS2.SetTextAlign(32);
	pCMS2.SetFillStyle(-1);
	pCMS2.SetBorderSize(0);
	pCMS2.AddText("L = 35.9 fb^{-1} (13 TeV)");
	gPad->Update();
	pCMS1.Draw("same");
	pCMS2.Draw("same");
	gPad->Update();
	pave.Draw("same");
	pCMS1.Draw("same");
	pCMS12.Draw("same");
	pCMS2.Draw("same");


	TLegend *leg = new TLegend(0.65,0.75,0.82,0.82);
	leg->SetFillColor(0);
	leg->SetBorderSize(0);
	leg->SetTextFont(42);
	leg->SetTextSize(0.025);
	leg->AddEntry(hist_mbb_reg,"Data","PE");
	leg->AddEntry(hist_mbb_reg_qcd,"QCD MC","ELP");
	leg->Draw("same");


	c_roo->Print("plots/VBF_profile_mbb_range"+type+".pdf");
//	c_roo->Print("plots/VBF_profile_mbb"+type+".pdf");



/*	
	TCanvas *c11 = new TCanvas();
	c11->SetBottomMargin(.15);
	c11->SetRightMargin(.25);
	c11->cd();
	TH1F *frame3 = new TH1F("frame3","",15,50.,200.);
	frame3->SetMinimum(0.);
   frame3->SetMaximum(hist_mbb_JEdown->GetMaximum()*1.6);
   frame3->SetStats(0);
	frame3->SetYTitle("Events");
	frame3->SetXTitle(hist_mbb_JEdown->GetXaxis()->GetTitle());
	frame3->GetYaxis()->SetNdivisions(505);
	frame3->GetXaxis()->SetLabelSize(0.0);
  	frame3->GetXaxis()->SetTitleSize(0.05);
  	frame3->GetXaxis()->SetLabelSize(0.04);
	frame3->Draw();
	TLatex* tex = new TLatex(0.75,0.95,"13 TeV");
   tex->SetNDC();
	tex->SetTextAlign(35);
   tex->SetTextFont(42);
   tex->SetTextSize(0.035);
   tex->SetLineWidth(2);
   TLatex *tex1 = new TLatex(0.17,0.95,"CMS");
   tex1->SetNDC();
   tex1->SetTextAlign(20);
   tex1->SetTextFont(61);
   tex1->SetTextSize(0.04);
   tex1->SetLineWidth(2);
   TLatex* tex2 = new TLatex(0.25,0.89,"Work in progress");
   tex2->SetNDC();
   tex2->SetTextAlign(20);
   tex2->SetTextFont(52);
   tex2->SetTextSize(0.035);
  	tex2->SetLineWidth(2);	
	TLatex* tex_file = new TLatex(0.36,0.95,text_type);
   tex_file->SetNDC();
	tex_file->SetTextAlign(35);
   tex_file->SetTextFont(42);
   tex_file->SetTextSize(0.04);
   tex_file->SetLineWidth(2);	
	tex->Draw();
	tex1->Draw();
	tex2->Draw();
//	tex_file->Draw();
	hist_mbb_JEdown->SetLineColor(8);
	hist_mbb_JEdown->SetLineWidth(2);
	hist_mbb_JEdown->Draw("PEsame");
//	c11->Print("plots/shape/v14_vbf"+type+"_"+jec+"_mbb_"+cats_names[cat_num]+corType[i]+".png");
*/

	return 0;

}

