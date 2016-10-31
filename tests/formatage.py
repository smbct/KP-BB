#!/usr/bin/env python
import sys

fichier = open(sys.argv[1])
cont = fichier.read()
fichier.close()

fichier = open(sys.argv[1] + 'format', 'w')

lignes = cont.splitlines()

for ligne in lignes:
    parties = ligne.split()
    parties[0] = parties[0].replace('_', '\\_')
    for i in range (2, 7):
        if i % 2 == 0:
            parties[i] = parties[i].split('.')[0]
    ligne = ''
    for i in range(0,7):
        ligne += parties[i] + ' '
    ligne += '\\\\' + '\n'
    fichier.write(ligne)
fichier.close()
