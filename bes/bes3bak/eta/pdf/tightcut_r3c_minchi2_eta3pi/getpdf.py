import ROOT
from ROOT import  TCanvas, TFile, TChain, TH1F, TTree, TCut, RooArgSet
from ROOT import  RooRealVar, RooDataSet, RooKeysPdf, RooWorkspace, RooPlot
from ROOT import *
from ROOT.RooFit import *
gROOT.SetBatch(1)
energy = [4600, 4612, 4620, 4640, 4660, 4680, 4700]

xmin = 2.25
xmax = 2.34919
xbins = 25
mbcmin = 2.25
mbcmax = 2.34919
cut_mbc = "((M_BC_r3c>=2.25) && (M_BC_r3c<=2.34919))"
# cut_deltaE_sig = "((deltaE_min>-0.03) && (deltaE_min<0.02))"
# cut_deltaE_ref = "((deltaE_min>-0.03) && (deltaE_min<0.02))"
cut_deltaE_sig = "(chi2_min_r3c<17 && np!=0 && npbar !=0 )"
cut_deltaE_ref = "(chi2_min_r3c<17 && np!=0 && npbar !=0 ) && (dipim<0.44 || dipim>0.52)"
cut_sig = (cut_mbc + " && "+  cut_deltaE_sig)
cut_ref = (cut_mbc  + " && "+  cut_deltaE_ref)

# M_BC_r3c = RooRealVar("M_BC_r3c", "M_BC_r3c", mbcmin, mbcmax)

xmin = 2.25 
xmax_4600 = 2.299765
xmax_4612 = 2.30579
xmax_4620 = 2.31387
xmax_4640 = 2.320255
xmax_4660 = 2.33046
xmax_4680 = 2.34079
xmax_4700 = 2.34919

var_4600 = RooRealVar("M_BC_r3c","M_{BC}", xmin, xmax_4600) 
var_4612 = RooRealVar("M_BC_r3c","M_{BC}", xmin, xmax_4612) 
var_4620 = RooRealVar("M_BC_r3c","M_{BC}", xmin, xmax_4620) 
var_4640 = RooRealVar("M_BC_r3c","M_{BC}", xmin, xmax_4640) 
var_4660 = RooRealVar("M_BC_r3c","M_{BC}", xmin, xmax_4660) 
var_4680 = RooRealVar("M_BC_r3c","M_{BC}", xmin, xmax_4680) 
var_4700 = RooRealVar("M_BC_r3c","M_{BC}", xmin, xmax_4700) 

var=[ var_4600, var_4612, var_4620, var_4640, var_4660, var_4680, var_4700]
name=["4600", "4612", "4620", "4640", "4660", "4680", "4700"]

can = TCanvas("can", "pdf", 800, 4200) 
can.Divide(2, 7)
sig_fileDirPath="/publicfs/ucas/user/yuanchy8/7.0.6/eta/shape_new/cutmassroot/tightcut_r3c_minchi2_eta3pi/"
# ref_fileDirPath="/publicfs/ucas/user/yuanchy8/7.0.6/pi0/shape/cutmassroot/tightcut_r3c_minchi2/"
#%% __ sig __
sig_filepath = []
sig_filepath.append(sig_fileDirPath + "4600shape.root")
sig_filepath.append(sig_fileDirPath + "4612shape.root")
sig_filepath.append(sig_fileDirPath + "4620shape.root")
sig_filepath.append(sig_fileDirPath + "4640shape.root")
sig_filepath.append(sig_fileDirPath + "4660shape.root")
sig_filepath.append(sig_fileDirPath + "4680shape.root")
sig_filepath.append(sig_fileDirPath + "4700shape.root")
#%% __ ref __
# ref_filepath=[]
# ref_filepath.append(ref_fileDirPath + "4600shape_adddipim.root")
# ref_filepath.append(ref_fileDirPath + "4612shape_adddipim.root")
# ref_filepath.append(ref_fileDirPath + "4620shape_adddipim.root")
# ref_filepath.append(ref_fileDirPath + "4640shape_adddipim.root")
# ref_filepath.append(ref_fileDirPath + "4660shape_adddipim.root")
# ref_filepath.append(ref_fileDirPath + "4680shape_adddipim.root")
# ref_filepath.append(ref_fileDirPath + "4700shape_adddipim.root")

# for sig

for i in range(0, len(sig_filepath)):
    print(" ***** bulid PDF *****: {}".format(sig_filepath[i]))
    chain = TChain("tree")
    chain.Add(sig_filepath[i])

    tr_shape = chain.CopyTree(cut_sig, "")
    shape = RooDataSet("shape", "mBC(GeV)", tr_shape, RooArgSet( var[i]))

    wspace_sig = RooWorkspace("wspace", "wspace_sig title")
    shapepdf = RooKeysPdf("modelPdf", "",  var[i], shape, RooKeysPdf.NoMirror)  
    # wspace_sig.Import(shapepdf) 
    getattr(wspace_sig,'import')(shapepdf)
    wspace_sig.writeToFile(sig_fileDirPath + "../../../pdf/tightcut_r3c_minchi2_eta3pi//{}_sig_shapepdf.root".format(str(energy[i])))

    # draw
    frame =  var[i].frame(ROOT.RooFit.Title("{} eta".format(str(energy[i]))), ROOT.RooFit.Bins(25))
    shapepdf.plotOn(frame, ROOT.RooFit.LineStyle(kDashed), ROOT.RooFit.LineColor(2)) 
    can.cd(i+1) 
    frame.Draw()


# for ref 

# for i in range(0, len(ref_filepath)):
#     print(" ***** bulid PDF *****: {}".format(ref_filepath[i]))
#     chain = TChain("tree")
#     chain.Add(ref_filepath[i])

#     tr_shape = chain.CopyTree(cut_ref, "")
#     shape = RooDataSet("shape", "mBC(GeV)", tr_shape, RooArgSet( var[i]))

#     shapepdf = RooKeysPdf("modelPdf", "",  var[i], shape, RooKeysPdf.NoMirror)  
#     wspace_ref = RooWorkspace("wspace", "wspace_ref title")
#     # wspace_ref.import(shapepdf) 
#     getattr(wspace_ref,'import')(shapepdf)
#     wspace_ref.writeToFile( ref_fileDirPath+ "../../../pdf/tightcut_r3c_minchi2//{}_ref_shapepdf.root".format(str(energy[i])))
#     # draw 
#     frame =  var[i].frame(ROOT.RooFit.Title("{} omega".format(str(energy[i]))), ROOT.RooFit.Bins(25))
#     shapepdf.plotOn(frame, ROOT.RooFit.LineStyle(kDashed), ROOT.RooFit.LineColor(2)) 
#     can.cd(i+8) 
#     frame.Draw()



can.SaveAs("shapepdf.png")


