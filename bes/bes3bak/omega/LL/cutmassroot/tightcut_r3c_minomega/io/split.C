TRandom3 rnd(10);
double n = 0;   
double nevt  = 100;

void split()
{

    string files[]={
"../4600LL_selB.root", 
"../4612LL_selB.root", 
"../4620LL_selB.root", 
"../4640LL_selB.root", 
"../4660LL_selB.root", 
"../4680LL_selB.root", 
"../4700LL_selB.root"
    };

    string outNames[]={
    "4600LL", 
    "4612LL", 
    "4620LL", 
    "4640LL", 
    "4660LL", 
    "4680LL", 
    "4700LL" 
    };

        auto getrndm = []( ) 
        {         
            
            // cout << __LINE__  << " " << rnd.Rndm() << endl;
            n = n+1;
            return  n/nevt; 

        };

    // for(int io=0; io<7; io++)
    {   
        // auto cutcut = "rndm<" + to_string(0.05*(io+1)) +  " && rndm>=" + to_string(0.05*io);
        // cout << cutcut <<endl;
        for(int i=0; i<7; i++)
        {

            ROOT::RDataFrame rdf("tree", files[i]);
            n = 0;
            auto c = rdf.Count();
            nevt = *c;

            auto  rdf2 = rdf.Define("rndm", getrndm)
                            // .Filter("M_BC_r3c>2.2 && np!=0 && npbar!=0 && etaprimemr3c>0.76 && etaprimemr3c<0.8")
                            // .Filter(cutcut)
                            ;
                            
            std::vector<std::string> branchList = 
                    {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c",
                    "signal", "rndm"
                    }; 
                        // rdf2.Snapshot("tree", "AAA_removedouble.root", branchList );
            // rdf2.Snapshot("tree", outNames[i] + "_io_" +  to_string(io) + ".root");    
            rdf2.Snapshot("tree", outNames[i] + "_io" + ".root");    

        }
    }
}
