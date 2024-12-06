TRandom3 rnd(10);
void LLsplit()
{

    ROOT::RDataFrame rdf("tree", "LL.root");

    auto getrndm = []( ) 
        {         
            
            // cout << __LINE__  << " " << rnd.Rndm() << endl;
            return  rnd.Rndm(); 

        };

    auto  rdf2 = rdf.Define("rndm", getrndm)
					// .Filter("(chi2_min_r3c<17) &&((M_BC_r3c>=2.25) && (M_BC_r3c<=2.34919)) && (np !=0 && npbar != 0)  ")
                    .Filter("rndm<0.05");

                    

    // std::vector<std::string> branchList = 
    //         {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c","flag1", 
    //          "mode1", "mode2", "mode3", "dipim","signal"
    //         }; 

    // rdf2.Snapshot("tree", "AAA_removedouble.root", branchList );
    rdf2.Snapshot("tree", "AAA_selB_split.root");    
}
