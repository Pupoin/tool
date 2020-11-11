# %%
# python3, run like: python3 getX.py inclusive
import os, re, math, sys, shutil

arg = sys.argv[1]
# arg = 'inclusive'
writeFile = open('.' + arg + '.getX', 'w')


pathLog = './log'
pathRoot = './root'
if os.path.exists(pathRoot+'/wrong') == False:
    os.makedirs(pathRoot+'/wrong')

logFiles = os.listdir(pathLog)
rootFiles = os.listdir(pathRoot)

falseFormatRootFiles = []
trueFormatRootFiles = []

# get the root files with right name format in pathRoot
for root in rootFiles:
    # inclusive_12894116_1000.root
    isTrueRoot = re.match(arg+'_[0-9]*_[0-9]*\.root', root)
    if isTrueRoot == None:
        falseFormatRootFiles.append(root)
        #shutil.move(pathRoot+'/'+root, pathRoot+'/wrong/')
        continue
    trueFormatRootFiles.append(root)

#print(falseFormatRootFiles)
#print(trueFormatRootFiles)


# %%
# get the dict: log-root
tmp_dictLog_root = dict()
for root in trueFormatRootFiles:
    split = re.split('_|\.', root)
    logFileName = split[0] + '.err_' + split[1] + '_' + split[2]
    tmp_dictLog_root[logFileName] = root

#print(tmp_dictLog_root)

# %%
# remove the root file which has no corresponding log(err) file
dictLog_root = dict()
for dictLog in tmp_dictLog_root.keys():
    if dictLog not in logFiles:
        continue
    dictLog_root[dictLog] = tmp_dictLog_root.get(dictLog)

#print(dictLog_root)


# %%
# get cross section
dictprocess = []
flagFordict = 0
for log in dictLog_root.keys():
    logString = open(pathLog + '/' + log).read()
    #logString = open("log/012j.err_1603857958_28").read()

    findword = 'Overall cross-section summary.*Before matching: total cross section ='
    pattern = re.compile(findword, flags=re.DOTALL)
    results = pattern.findall(logString)
    
    if results == []:
        shutil.move(pathRoot+'/'+dictLog_root.get(log), pathRoot+'/wrong/')
        continue
    
    tmp = results[0].split("\n")
    d = 0
    for j in range(len(tmp)): 
        if j==0 or j==1 or j==2 or j==len(tmp)-1 or j==len(tmp)-2 or j==len(tmp)-3 or j==len(tmp)-4:
            continue
        if flagFordict == 0:
            dictprocess.append({})

        tmp1 = tmp[j].split("\t") # save process i  
        tmp_xsec_err = tmp1[2]    # 1.719e+03 +/- 1.058e+01
        tmp2 = tmp_xsec_err.split(" ")
        # like {'012j.err_1603835470_19_process_1 3.571e+03': '1.149e+01'}
        dictprocess[d].update({log + '_process_' + str(d) + ' ' + tmp2[0]: tmp2[2]})
        d = d + 1

    flagFordict = 1
    print(dictprocess[2])
    print("\n\n\n\n\n\n")
    # print(pathRoot+'/' + dictLog_root.get(log) + '  ' + pathLog +
    #       '/' + log + '  ' + xsec + ' +- ' + dictXsec_err[log+" " + xsec])
   
    #writeFile.write(pathRoot+'/' + dictLog_root.get(log) + '  ' + pathLog +
    #      '/' + log + '  ' + xsec + ' +- ' + dictXsec_err[log+" " + xsec] + '\n')

#print(dictXsec_err_p0)


# %%
# calculate the total cross and error
#finalValue = 0
#finalError = 0
#
#for xsec in dictXsec_err.keys():
#    tmp = xsec.split(" ")
#    currentValue = float(tmp[1])
#    currentError = float(dictXsec_err.get(xsec))
#
#    if (finalValue <= 0):
#        finalValue = currentValue
#        finalError = currentError
#    else:
#        wgt1 = finalWeight if (
#            finalError <= 0 or currentError <= 0) else 1 / (finalError * finalError)
#        wgt2 = currentWeight if (
#            finalError <= 0 or currentError <= 0) else 1 / (currentError*currentError)
#
#        xsec = (wgt1 * finalValue + wgt2 * currentValue) / (wgt1 + wgt2)
#        err = 0 if (finalError <= 0 or currentError <=
#                    0) else 1.0 / math.sqrt(wgt1 + wgt2)
#        finalValue = xsec
#        finalError = err
#
#
## %%
## output
#
#print("run ok file num: "+str(len(dictXsec_err)))
#print('xsec +- err: ' + str(round(finalValue, 6)) +
#      " +- " + str(round(finalError, 6)) + ' pb')
#
#writeFile.write('\n')
#writeFile.write("run ok file num: "+str(len(dictXsec_err)) + '\n')
#writeFile.write('xsec +- err: '+str(finalValue) +
#                " +- " + str(finalError) + ' pb\n')
#
#writeFile.close()
#
## %%
#
