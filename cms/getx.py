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
dictXsec_err = dict()
for log in dictLog_root.keys():
    logString = open(pathLog + '/' + log).read()

    findword = 'After matching: total cross section =.*'
    pattern = re.compile(findword)
    results = pattern.findall(logString)

    if results == []:
        shutil.move(pathRoot+'/'+dictLog_root.get(log), pathRoot+'/wrong/')
        continue

    tmp = results[0].split(" ")

    xsec = tmp[6]
    xsecError = tmp[8]
    dictXsec_err[log+' ' + xsec] = xsecError

    # print(pathRoot+'/' + dictLog_root.get(log) + '  ' + pathLog +
    #       '/' + log + '  ' + xsec + ' +- ' + dictXsec_err[log+" " + xsec])
   
    writeFile.write(pathRoot+'/' + dictLog_root.get(log) + '  ' + pathLog +
          '/' + log + '  ' + xsec + ' +- ' + dictXsec_err[log+" " + xsec] + '\n')

# print(dictXsec_err)


# %%
# calculate the total cross and error
finalValue = 0
finalError = 0

for xsec in dictXsec_err.keys():
    tmp = xsec.split(" ")
    currentValue = float(tmp[1])
    currentError = float(dictXsec_err.get(xsec))

    if (finalValue <= 0):
        finalValue = currentValue
        finalError = currentError
    else:
        wgt1 = finalWeight if (
            finalError <= 0 or currentError <= 0) else 1 / (finalError * finalError)
        wgt2 = currentWeight if (
            finalError <= 0 or currentError <= 0) else 1 / (currentError*currentError)

        xsec = (wgt1 * finalValue + wgt2 * currentValue) / (wgt1 + wgt2)
        err = 0 if (finalError <= 0 or currentError <=
                    0) else 1.0 / math.sqrt(wgt1 + wgt2)
        finalValue = xsec
        finalError = err


# %%
# output

print("run ok file num: "+str(len(dictXsec_err)))
print('xsec +- err: ' + str(round(finalValue, 6)) +
      " +- " + str(round(finalError, 6)) + ' pb')

writeFile.write('\n')
writeFile.write("run ok file num: "+str(len(dictXsec_err)) + '\n')
writeFile.write('xsec +- err: '+str(finalValue) +
                " +- " + str(finalError) + ' pb \n')

writeFile.close()

# %%

