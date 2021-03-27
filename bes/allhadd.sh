myallhadd()
{
    if [ x"${1}" == x"" ]
    then
        echo "error ~! please run like: myallhadd <path> "
        return 1
    fi
    mKdir -p ${1}
    
    cd LL/root
    pwd
    hadd LL.root ana_*root
    mv LL.root ../../0ana/root
    cd -
    
    cd data/root/
    pwd
    hadd data.root ana_*root
    mv data.root ../../0ana/root
    cd -
    
    cd hadron/root
    pwd
    hadd hadron.root ana*root
    mv hadron.root ../../0ana/root
    cd -
    
    cd shape/ana/root
    pwd
    hadd shape.root ana*root
    mv shape.root ../../../0ana/root
    cd -
    
    cd signal/ana/root
    pwd
    hadd signal.root an*root
    mv signal.root ../../../0ana/root
    cd -
}
