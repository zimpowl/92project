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
  print( '=' * 25 + ' SUITE TEST ' + '=' * 25 )
  print( '\n' )

def header(category):
  print( '=' * 15 + ' ', category, ' ' + '=' * 15)
  print( '\n' )

def start_test(category):
  timer_start = default_timer()
  header(category.upper())
  total = 0
  index = 0
  
  for index, filename in enumerate(glob.glob(category + '/*')):
    if default_timer() - timer_begin > float(timer) and parsed.timeout:
      print(timer, "secondes past...  TIME DONE !!")
      exit(1)
    chronos = default_timer()
    
    with open(filename) as f:
      conf = yaml.load(f)
    f.close()
    
    
    if parsed.sanity:
      commands.insert(0, "valgrind")

    try:
      commands1 = ["./42sh", "-c", conf['input'] ]
      commands2 = ["bash", "--posix", "-c", conf['input'] ]

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
      value = "OK"
      total = total + 1
    else:
      value = "KO"	
      exit_code = 1
    
    result_value =  ' ' * (69 - len(conf['input'])) + str(value)
    timer_value = default_timer() - chronos
    
    print('#' + str(index + 1), ' ', conf['input'], result_value, "["+str(exit_code2)+"]", timeout(chronos))
  
  percent = round((total/ (index +1)) * 100, 1)
  
  status = " SUCCESS "
  if percent < 50:
    status = "   FAIL  "
    
  print(' '*(70 - len(str(percent))) + str(percent) + '%', status, timeout(timer_start))



def timeout(timer):
  return '  ' + str(round(default_timer() - timer, 4)) + " s"

if parsed.list:
  print("lists")
  print("commands")
  print("ands")
  print("ors")
  print("pipes")
  print("multiples")
  print("if")
  print("while")
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
  start_test("lists")
  start_test("commands")
  start_test("ands")
  start_test("ors")
  start_test("pipes")
  start_test("multiples")
  start_test("if")
  start_test("while")
  exit(0)
