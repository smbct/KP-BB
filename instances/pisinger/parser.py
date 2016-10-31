#!/usr/bin/env python
import sys

def creerInstance(debut, fin, lignes, num):

    fname = open(lignes[debut]+'.dat', 'w')

    nbVar = int((lignes[debut+1].split())[1])
    capa = int((lignes[debut+2].split())[1])
    debut = debut + 5
    profit = ''
    poids = ''
    while debut < fin:
        sep = lignes[debut].split(',')
        # d'abord profit, poids ensuite
        profit += sep[1]
        poids += sep[2]
        if debut < fin-1:
            profit += ' '
            poids += ' '
        debut += 1

    # enregistrement dans un fichier

    fname.write(str(nbVar))
    fname.write('\n')
    fname.write(profit)
    fname.write('\n')
    fname.write(str(capa))
    fname.write('\n')
    fname.write(poids)
    fname.close()


fname = open(sys.argv[1])
cont = fname.read()
fname.close()

lignes = cont.splitlines()

continuer = True

debut = 0
fin = 0
finFichier = False
nb = 0
while not finFichier:

    continuer = True
    while continuer:
        if lignes[fin][0] == '-':
            continuer = False
        else:
            fin += 1

    nb += 1

    creerInstance(debut, fin, lignes, nb)

    debut = fin+2
    fin = debut

    if debut >= len(lignes):
        finFichier = True
