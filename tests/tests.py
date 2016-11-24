#!/usr/bin/env python3
import glob
import yaml
import subprocess
import argparse
from timeit import default_timer

parser = argparse.ArgumentParser()
parser.add_argument("-l", "--list", action='store_true')
parser.add_argument("-c", "--category")
parser.add_argument("-s", "--sanity", action='store_true')
parser.add_argument("-t", "--timeout")
parsed = parser.parse_args()


timer = 0
timer_begin = default_timer();

def first_header():
  print( '=' * 25 + ' \033[33mSUITE TEST\033[37m ' + '=' * 25 )
  print( '\n' )

def header(category):
  print( '=' * 15 + ' \033[36m', category, '\033[37m ' + '=' * 15)
  print( '\n' )

def start_test(category):
  timer_start = default_timer()
  header(category.upper())
  total = 0
  index = 0
  
  for index, filename in enumerate(glob.glob(category + '/*')):
    if default_timer() - timer_begin > float(timer) and parsed.timeout:
      print(timer, "\033[31msecondes past...  TIME DONE !!\033[37m")
      exit(1)
    chronos = default_timer()
    
    with open(filename) as f:
      conf = yaml.load(f)
    f.close()
    
    
    if parsed.sanity:
      commands.insert(0, "valgrind")

    try:
      commands1 = ["bash", "--posix", "-c", conf['input'] ]
      commands2 = ["./42sh", "-c", conf['input'] ]

      sp1 = subprocess.run(commands1, stderr = subprocess.PIPE, stdout = subprocess.PIPE)
      err1 = sp1.stderr.decode('utf-8')
      out1 = sp1.stdout.decode('utf-8')
      exit_code1 = sp1.returncode

      sp2 = subprocess.run(commands2, stderr = subprocess.PIPE, stdout = subprocess.PIPE)
      err2 = sp2.stderr.decode('utf-8')
      out2 = sp2.stdout.decode('utf-8')
      exit_code2 = sp2.returncode

      conf['stdout'] = out1
      conf['stderr'] = err1
      conf['exit_code'] = exit_code1
      conf['42stdout'] = out2
      conf['42stderr'] = err2
      conf['42exit_code'] = exit_code2

      with open(filename, 'w') as f:
        yaml.dump(conf, f, default_flow_style=False)

    except ValueError:
      print("error\n")
    
    if out1 == out2 and err1 == err2 and exit_code1 == exit_code2:
      value = "\033[32mOK\033[37m"
      total = total + 1
    else:
      value = "\033[31mKO\033[37m"	
      exit_code = 1
    
    result_value =  ' ' * (69 - len(conf['input'])) + str(value)
    timer_value = default_timer() - chronos
    
    print('#' + str(index + 1), ' ', conf['input'], result_value, "["+str(exit_code2)+"]", timeout(chronos))
  
  percent = round((total/ (index +1)) * 100, 1)
  
  status = " \033[32mSUCCESS\033[37m "
  if percent < 50:
    status = "   \033[31mFAIL\033[37m  "
  perc = str(percent)
  if percent < 26:
    perc = '\033[31m' + perc + '%\033[37m'
  else: 
    if percent < 76:
      perc = '\033[33m' + perc + '%\033[37m'
    else:
      perc = '\033[32m' + perc + '%\033[37m'
  print(' '*(70 - len(str(percent))) + perc , status, timeout(timer_start))



def timeout(timer):
  return ' \033[33m' + str(round(default_timer() - timer, 4)) + " s\033[37m"

if parsed.list:
  print("commands")
  print("export")
  print("ands")
  print("ors")
  print("testpipe")
  print("multiples")
  print("while")
  print("echo")
  print("testvalid")
  print("testfor")
  print("testif")
  print("testfunction")
  exit(0)

if parsed.timeout:
  timer = parsed.timeout

if parsed.sanity:
  exit_code = 0

if parsed.category:
  first_header()
  start_test(parsed.category)
  exit(0)
else:
  first_header()
  start_test("commands")
  start_test("ands")
  start_test("ors")
  start_test("testpipe")
  start_test("multiples")
  start_test("while")
  start_test("echo")
  start_test("testvalid")
  start_test("testfor")
  start_test("testif")
  start_test("testfunction")
  start_test("export")
  exit(0)
