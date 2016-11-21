#!/usr/bin/env python3
import argparse
import subprocess
import os
import time

start_time = time.time()

parser = argparse.ArgumentParser()
parser.add_argument("-l", "--list", action='store_true')
parser.add_argument("-s", "--sanity", action='store_true')
parser.add_argument("-c", "--category")
parser.add_argument("-t", "--timeout")
parsed = parser.parse_args()

if parsed.list:
  print("echo")
  print("globbing")
  print("pipes")

if parsed.category:
  print("category")
  
if parsed.sanity:
  print(parsed.sanity)

if parsed.timeout:
  print(parsed.timeout)




print("End of test suite.\n")
