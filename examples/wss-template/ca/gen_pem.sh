#!/bin/bash

openssl genrsa -out private.pem 2048
openssl req -new -x509 -key private.pem -out cacert.pem -days 10950
