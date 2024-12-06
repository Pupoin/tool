#include "RooAddPdf.h"
#include "RooChebychev.h"
#include "RooConstVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "RooWorkspace.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TCut.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TH1.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TLorentzVector.h"
#include "TString.h"
#include "TSystem.h"
#include "TTree.h"
#include "iostream"
#include "RooAbsReal.h"
#include "RooArgSet.h"
#include "RooDataSet.h"
#include "RooKeysPdf.h"
#include "RooRealVar.h"
#include "TChain.h"
#include <iomanip>

using namespace std;
using namespace RooFit;

int how_to_get_the_signalshape_pdf()
{
    // get data!!!
    TChain *chain_data = new TChain("tree");
    chain_data->Add("../root/shape.root");

    TCut cut_np = "(np !=0 && npbar != 0)";
    TCut cut_mass = "(etam>=0.5&&etam<=0.56 ) && (pi0m>=0.115&&pi0m<=0.15)";
    TCut cut_mbc = "((M_BC>=2.25) && (M_BC<=2.313))";
    TCut cut_chi2 = "(chi2_min_r1c<13)";
    TCut cut_sum1 = (cut_chi2 && cut_mbc && cut_mass && cut_np);

    TTree *tr_fit = chain_data->CopyTree(cut_sum1, "", 1000000000, 0);

    // Declare observable M_BC, which is similar to x.
    RooRealVar M_BC("M_BC", "M_BC", 2.25, 2.313, "");

    // Constructor importing event data from external ROOT Tree
    RooDataSet *data =
        new RooDataSet("data", "mBC(GeV)", tr_fit, RooArgSet(M_BC));

    // generate pdf!!!
    RooKeysPdf *pdf = new RooKeysPdf("pdf", "", M_BC, *data, RooKeysPdf::NoMirror);
    pdf->Print();

    // store the pdf in RooWorkspace: a persistable container for RooFit projects.
    RooWorkspace *wspace = new RooWorkspace("wspace", "wspace title");
    wspace->import(*pdf);
    wspace->writeToFile("pdfLambdacSigmaEtaShape.root");

    //   Workspace will remain in memory after macro finishes
    gDirectory->Add(wspace);

    // plot the pdf
    RooPlot *frame = M_BC.frame(
        Title("Adaptive kernel estimation pdf with and w/o mirroring"), Bins(25));
    pdf->plotOn(frame, LineStyle(kDashed), LineColor(kRed));
    data->plotOn(frame);
    frame->Draw();
    wspace->Print();
    return 0;
}
