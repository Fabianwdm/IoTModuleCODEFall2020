import flask
import sys
import os
from dotenv import load_dotenv
from firebase import Firebase
load_dotenv()

config = {
  "apiKey": os.getenv('APIKEY'),
  "authDomain": os.getenv('AUTHDOMAIN'),
  "databaseURL": os.getenv('DATABASEURL'),
  "storageBucket": os.getenv('STORAGEBUCKET')
}

firebase = Firebase(config)