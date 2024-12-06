TRandom3 rnd(10);
double n = 0;   
double nevt  = 100;
void split()
{

    string files[]={
    "../4600LL.root", 
    "../4612LL.root", 
    "../4620LL.root", 
    "../4640LL.root", 
    "../4660LL.root", 
    "../4680LL.root", 
    "../4700LL.root" 
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
            auto num = rdf0.Count();
            double numm = *num;
            auto rdf = rdf0//.Range(int(numm*0.57))
                            .Filter("(chi2_min_r3c<17) &&((M_BC_r3c>=2.25) && (M_BC_r3c<=2.34919)) && (np !=0 && npbar != 0)  ");

            n = 0;  
            auto c = rdf.Count();
            nevt = *c;
            cout << nevt << endl;
            auto  rdf2 = rdf.Define("rndm", getrndm)
                            // .Filter("(chi2_min_r3c<17) &&((M_BC_r3c>=2.25) && (M_BC_r3c<=2.34919)) && (np !=0 && npbar != 0)  ");

                            // .Filter(cutcut)
                            ;
                            
        std::vector<std::string> branchList = 
                {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c",
                "signal", "rndm"
                }; 
            rdf2.Snapshot("tree", outNames[i] + "_io" + ".root", branchList);    

        }
    }
}
