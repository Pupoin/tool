TRandom3 rnd(10);
double n = 0;   
double nevt  = 100;
void split()
{

    string files[]={
    "4600hadron.root", 
    "4612hadron.root", 
    "4620hadron.root", 
    "4640hadron.root", 
    "4660hadron.root", 
    "4680hadron.root", 
    "4700hadron.root"
    };
    double scale[] =  {1, 1, 0.5, 0.5, 0.5, 1, 0.5};
    string outNames[]={
    "4600hadron", 
    "4612hadron", 
    "4620hadron", 
    "4640hadron", 
    "4660hadron", 
    "4680hadron", 
    "4700hadron" 
    };

        auto getrndm = []( ) 
        {         
            
            // cout << __LINE__  << " " << rnd.Rndm() << endl;
            // return  rnd.Rndm(); 
            n = n+1;
            return  n/nevt; 

        };

    // for(int io=0; io<7; io++)
    {   
        // auto cutcut = "rndm<" + to_string(0.05*(io+1)) +  " && rndm>=" + to_string(0.05*io);
        // cout << cutcut <<endl;
        for(int i=0; i<7; i++)
        {

            ROOT::RDataFrame rdf0("tree", files[i]);
            auto rdf = rdf0.Filter("flag1!=96"); //.Filter("(chi2_min_r3c<17) &&((M_BC_r3c>=2.25) && (M_BC_r3c<=2.34919)) && (np !=0 && npbar != 0)  ");
            n = 0;
            auto c = rdf.Count();
            nevt = *c;
            cout << nevt << endl;
            auto  rdf2 = rdf.Range(scale[i] * nevt)
                            // .Define("rndm", getrndm)
                            
                            ;
                            
            std::vector<std::string> branchList = 
                    {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c","flag1", 
                     "mode1", "mode2", "mode3","signal"
                    }; 
            // rdf2.Snapshot("tree", "AAA_removedouble.root", branchList );
            // rdf2.Snapshot("tree", outNames[i] + "_io_" +  to_string(io) + ".root");    
            rdf2.Snapshot("tree", outNames[i] + "_selB" + ".root", branchList);    
        }
    }
}
