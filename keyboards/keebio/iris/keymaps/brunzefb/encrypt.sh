#!/bin/bash
sops -e secrets.h > secrets.enc.h
git add secrets.enc.h
