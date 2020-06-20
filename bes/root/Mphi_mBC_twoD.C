#include "TCanvas.h"
#include "TStyle.h"
#include "/afs/ihep.ac.cn/users/l/lincx/useful/boot.h"
void Mphi_mBC_twoD()
{
		setStyle();myStyle->SetTitleXSize(0.06);//myStyle->SetTitleXOffset(1.2);
		myStyle->SetTitleYSize(0.05);//myStyle->SetTitleYOffset(1.2);
		TCanvas *can = new TCanvas("can","",800,600); 
		can->SetFillColor(0);
		can->SetFrameFillColor(0);
		can->SetLeftMargin(0.15);
		can->SetRightMargin(0.1);
		can->SetTopMargin(0.1);
		can->SetBottomMargin(0.15);
		gStyle->SetOptStat(0);

		//================= set axis ===================
		Double_t ymin=0.987, ymax=1.085;  Double_t ybins=100;
		Double_t xmin=1.830, xmax=1.887;  Double_t xbins=100;
		TChain *data = new TChain("TDphipi"); 
		data->Add("/scratchfs/bes/lincx/6.6.4.p02/DptoPhiPi/job_ana/root/all_deltaE.root"); //data

		//==================mode cut!!!!!!!!!=========================//
		TCut cut_dE = "(dE_min>-0.020&&dE_min<0.019)";
		TCut cut_mbc = "(mbc_1>1.80&&mbc_1<1.8865)";
		TCut cut_mphi= "(M_phi>0.987354&&M_phi<1.10)";
		TCut sum = (cut_mbc&&cut_dE&&cut_mphi);


		//========================fill histo!!!!!====================================//
		TH2D *Mphi_mBC=new TH2D("mphi_mbc","",xbins,xmin,xmax,ybins,ymin,ymax);


		//==========================draw!!!!!========================
		can->cd();
		data->Draw("M_phi:mbc_1>>mphi_mbc",sum,"");
		Mphi_mBC->GetYaxis()->SetTitle("M_{K^{+}K^{-}}(GeV/c^{2})");
		Mphi_mBC->GetXaxis()->SetTitle("M_{BC}(GeV/c^{2})");

		TPaveText *pt = new TPaveText(0.22,0.78,0.5,0.85,"blNDC");
		pt->SetBorderSize(0);
		pt->SetFillColor(0);
		pt->SetLineColor(kBlack);
		//	pt->SetTextColor(5);
		TText *text; 
		//text = pt->AddText("SigMC: D^{+}#rightarrow#phi#pi^{+}");
		text = pt->AddText("signal process");
		pt->Draw();
		can->Update();
		//can->SaveAs("/afs/ihep.ac.cn/users/l/lincx/picture/phipi_sigMC_2D_distribution.eps");
}
