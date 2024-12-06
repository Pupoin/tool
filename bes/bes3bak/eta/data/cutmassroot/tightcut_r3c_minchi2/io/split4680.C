TRandom3 rnd(10);
void split4680()
{

    ROOT::RDataFrame rdf("tree", "4680data_removedouble.root");

    auto getrndm = []( ) 
        {         
            
            // cout << __LINE__  << " " << rnd.Rndm() << endl;
            return  rnd.Rndm(); 

        };

    auto  rdf2 = rdf.Define("rndm", getrndm)
                    .Filter("rndm<0.05");
                    

    // std::vector<std::string> branchList = 
    //         {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c","flag1", 
    //          "mode1", "mode2", "mode3", "dipim","signal"
    //         }; 

    // rdf2.Snapshot("tree", "4680data_removedouble.root", branchList );
    rdf2.Snapshot("tree", "4680data_removedouble_split.root");    
}
