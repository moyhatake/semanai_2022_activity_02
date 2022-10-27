import time
import psutil
import pyrebase

config = {
"apiKey": "AIzaSyD2hVFHxx6T6M-T9RpgrLSqJFySTg6D7gA",
"authDomain": "esp32-alonso.firebaseapp.com",
"databaseURL": "https://esp32-alonso-default-rtdb.firebaseio.com", 
"projectId": "esp32-alonso", 
"storageBucket": "esp32-alonso.appspot.com", 
"messagingSenderId": "950513851689", 
"appId": "1:950513851689:web:fa4cb47824acba2c3ceb38"
}

def getListOfProcessSortedByMemory():
    '''
    Get list of running process sorted by Memory Usage
    '''
    listOfProcObjects = []
    # Iterate over the list
    for proc in psutil.process_iter():
       try:
           # Fetch process details as dict
           pinfo = proc.as_dict(attrs=['pid', 'name', 'username'])
           pinfo['vms'] = proc.memory_info().vms / (1024 * 1024)
           # Append dict to list
           listOfProcObjects.append(pinfo);
       except (psutil.NoSuchProcess, psutil.AccessDenied, psutil.ZombieProcess):
           pass
    # Sort list of dict by key vms i.e. memory usage
    listOfProcObjects = sorted(listOfProcObjects, key=lambda procObj: procObj['vms'], reverse=True)
    return listOfProcObjects

def parseFrec():
    tmp_frec = str(psutil.cpu_freq())
    i = tmp_frec.find("current=") + 8
    f = tmp_frec.index(",")
    tmp_frec = tmp_frec[i:f].strip()
    return tmp_frec

def parseMem():
    tmp_mem = str(psutil.virtual_memory())
    i = tmp_mem.find("percent=") + 8
    f = tmp_mem.index(",", i)
    tmp_mem = tmp_mem[i:f].strip()
    return tmp_mem

def parseProc():
    tmp_proc = str(proc[0])
    i = tmp_proc.find("'name':") + 9
    f = tmp_proc.index("'", i)
    tmp_proc = tmp_proc[i:f].strip()
    return tmp_proc

firebase = pyrebase.initialize_app(config)
db = firebase.database()

# accesing database in firebase
db = firebase.database()
# reading some atributes of the onKey elements
all_users = db.child("users").get()

proc = getListOfProcessSortedByMemory()

while True:
    proc = getListOfProcessSortedByMemory()
    # create your onKey, for label elements
    # update elements
    db.child("users").child("Moy").push({"frec":str(parseFrec()), "nuc":str(psutil.cpu_count()), "uso":str(psutil.cpu_percent(4)), "mem":str(parseMem()), "proc":str(parseProc())})
    print("Data updated successfully ")
    time.sleep(30)

for users in all_users.each():
    print(users.val())
    print(users.key())