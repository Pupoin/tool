import ROOT
from ROOT import TRandom3
import time
import os
import argparse
import optparse

usage = 'usage: %prog [options]'
parser = optparse.OptionParser(usage)
parser.add_option('--seed', dest='seed', help='seed', default='234832', type='long')
parser.add_option('--ProcId', dest='ProcId', help='ProcId', type='long')
(opt, args) = parser.parse_args()

print("seed is ", opt.seed)


dir="new_root/"
energy=[4600, 4612, 4620, 4640, 4660, 4680, 4700]
ROOT.gRandom.SetSeed(opt.seed)

for i in range(0,50):
    toBeAdd = ROOT.gRandom.Gaus(0.30,0.70)

    dest_dir = "{0}/{1}_{2}".format(dir, opt.ProcId, i)
    os.system("mkdir -p {0}".format(dest_dir))
    os.system("cp all_covGaus.sh {0} ".format(dest_dir))
    os.system("cp covGaus.C {0}".format(dest_dir))
    
    print("---------- i = ", i, " toBeAdd = ",  toBeAdd , " dest_dir = ", dest_dir)
    os.system("cd {0} && sed \"s|ToBeAdd|{1}|\" -i covGaus.C && bash all_covGaus.sh &&  /bin/rm covGaus*.C && /bin/rm all_covGaus.sh && cd ../../".format(dest_dir, toBeAdd))
    # os.system("cd {0} && sed \"s|ToBeAdd|{1}|\" -i covGaus.C && bash all_covGaus.sh   && cd ../../".format(dest_dir, toBeAdd))
    time.sleep(2)

  


