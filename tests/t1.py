#!/usr/bin/env python
import glob
import yaml
import subprocess
import argparse
from timeit import default_timer





try:
  with open("command1.yml") as f:
    conf = yaml.load(f)
  f.close

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

  with open("command1.yml", 'w') as f:
    yaml.dump(conf, f, default_flow_style=False)

except ValueError:
  print("error\n")

