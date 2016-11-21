import subprocess
print ('='*8 + ' SUITE TEST ' + '='*8)

print ('\n')

def levelbegin(level):
  print ('====== level ', level, ' ======')
   
def levelend(): 
  print ('====== end ======')

def compare_files(out1, out2):
  with open(out1, 'r') as my_file:
    file1=set(my_file.readlines())

  with open(out2, 'r') as my_file:
    file2=set(my_file.readlines())

  open('out', 'w').close()

  with open('out', 'r') as my_file:
    for line in list(file1-file2):
      my_file.write(line)

  subprocess.call(["cat","out"])

def levels(level):
  if level == 1:
    subprocess.call(["./42sh", "-c", "ls"])
    subprocess.call(["bash", "--posix", "ls", ">", "out2"]) 
    subprocess.call(["cat ", ">", "out1"]) 
    compare_files("out1", "out2")

levelbegin(1)
levels(1)
levelend() 
