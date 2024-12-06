import ROOT
from ROOT import  TCanvas, TFile, TChain, TH1F, TTree, TCut, RooArgSet
from ROOT import  RooRealVar, RooDataSet, RooKeysPdf, RooWorkspace, RooPlot
from ROOT import *
from ROOT.RooFit import *

energy = [4600, 4612, 4620, 4640, 4660, 4680, 4700]

xmin = 2.25
xmax = 2.34919
xbins = 25
mbcmin = 2.25
mbcmax = 2.34919
cut_mbc = "((M_BC_c>=2.25) && (M_BC_c<=2.34919))"
cut_deltaE_sig = "((deltaE_min_c>-0.027) && (deltaE_min_c<0.021)) && (np!=0 && npbar!=0)"
cut_deltaE_ref = "((deltaE_min_c>-0.027) && (deltaE_min_c<0.021)) && (np!=0 && npbar!=0)"
cut_sig = (cut_mbc + " && " +  cut_deltaE_sig )
cut_ref = (cut_mbc + " && " + cut_deltaE_ref)
M_BC_c = RooRealVar("M_BC_c", "M_BC_c", mbcmin, mbcmax)


can = TCanvas("can", "pdf", 800, 4200) 
can.Divide(2, 7)
sig_fileDirPath="/publicfs/ucas/user/yuanchy8/7.0.6/eta/shape/cutmassroot/tightcut_zhou2me/"
ref_fileDirPath="/publicfs/ucas/user/yuanchy8/7.0.6/pi0/shape/cutmassroot/tightcut_zhou2me/"
#%% __ sig __
sig_filepath = []
# sig_filepath.append(sig_fileDirPath + "4600shape_removedouble.root")
# sig_filepath.append(sig_fileDirPath + "4612shape_removedouble.root")
# sig_filepath.append(sig_fileDirPath + "4620shape_removedouble.root")
# sig_filepath.append(sig_fileDirPath + "4640shape_removedouble.root")
# sig_filepath.append(sig_fileDirPath + "4660shape_removedouble.root")
# sig_filepath.append(sig_fileDirPath + "4680shape_removedouble.root")
# sig_filepath.append(sig_fileDirPath + "4700shape_removedouble.root")
#%% __ ref __
ref_filepath=[]
ref_filepath.append(ref_fileDirPath + "4600shape_removedouble.root")
ref_filepath.append(ref_fileDirPath + "4612shape_removedouble.root")
ref_filepath.append(ref_fileDirPath + "4620shape_removedouble.root")
ref_filepath.append(ref_fileDirPath + "4640shape_removedouble.root")
ref_filepath.append(ref_fileDirPath + "4660shape_removedouble.root")
ref_filepath.append(ref_fileDirPath + "4680shape_removedouble.root")
ref_filepath.append(ref_fileDirPath + "4700shape_removedouble.root")

# for sig
for i in range(0, len(sig_filepath)):
    print(" ***** bulid PDF *****: {}".format(sig_filepath[i]))
    chain = TChain("tree")
    chain.Add(sig_filepath[i])

    tr_shape = chain.CopyTree(cut_sig, "")
    shape = RooDataSet("shape", "mBC(GeV)", tr_shape, RooArgSet(M_BC_c))

    shapepdf = RooKeysPdf("modelPdf", "", M_BC_c, shape, RooKeysPdf.NoMirror)  
    wspace = RooWorkspace("wspace", "wspace title")
    # wspace.Import(shapepdf) 
    getattr(wspace,'import')(shapepdf)

    wspace.writeToFile(sig_fileDirPath + "../../../pdf/tightcut_zhou2me//{}_sig_shapepdf.root".format(str(energy[i])))
    
    frame = M_BC_c.frame(ROOT.RooFit.Title("{} eta".format(str(energy[i]))), ROOT.RooFit.Bins(25))
    shapepdf.plotOn(frame, ROOT.RooFit.LineStyle(kDashed), ROOT.RooFit.LineColor(2)) 
    can.cd(i+1) 
    frame.Draw()

# for ref 
for i in range(0, len(ref_filepath)):
    print(" ***** bulid PDF *****: {}".format(ref_filepath[i]))
    chain = TChain("tree")
    chain.Add(ref_filepath[i])

    tr_shape = chain.CopyTree(cut_ref, "")
    shape = RooDataSet("shape", "mBC(GeV)", tr_shape, RooArgSet(M_BC_c))

    shapepdf = RooKeysPdf("modelPdf", "", M_BC_c, shape, RooKeysPdf.NoMirror)  
    wspace = RooWorkspace("wspace", "wspace title")
    # wspace.import(shapepdf) 
    getattr(wspace,'import')(shapepdf)
    
    wspace.writeToFile( ref_fileDirPath+ "../../../pdf/tightcut_zhou2me//{}_ref_shapepdf.root".format(str(energy[i])))
    
    frame = M_BC_c.frame(ROOT.RooFit.Title("{} omega".format(str(energy[i]))), ROOT.RooFit.Bins(25))
    shapepdf.plotOn(frame, ROOT.RooFit.LineStyle(kDashed), ROOT.RooFit.LineColor(2)) 
    can.cd(i+8) 
    frame.Draw()

can.SaveAs("shapepdf.png")


