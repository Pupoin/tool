TRandom3 rnd(10);
void split()
{

    ROOT::RDataFrame rdf("tree", "AAA_selB.root");

    auto getrndm = []( ) 
        {         
            
            // cout << __LINE__  << " " << rnd.Rndm() << endl;
            return  rnd.Rndm(); 
        };

    auto  rdf2 = rdf.Define("rndm", getrndm)
                    .Filter("rndm<0.1")
                    .Filter("signal==1 || signal==-1")
                    
                    ;
                    

    // std::vector<std::string> branchList = 
    //         {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c","flag1", 
    //          "mode1", "mode2", "mode3", "dipim","signal"
    //         }; 

    // rdf2.Snapshot("tree", "AAA_removedouble.root", branchList );
    rdf2.Snapshot("tree", "AAA_selB_split.root");    
}
