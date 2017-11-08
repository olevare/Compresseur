#!/usr/bin/python
# -*-coding:utf-8-*-

import os,sys,re,time

def temp(): #juste parce que c'est classe 
      nbr=0
      while nbr!=10 :
            time.sleep(0.25)
            print"  ."
            nbr+=1           
      print "-----------------------------------------------------------------------"
      
res="a"
#creation d'une variable globale 
# 1 fonction qui demande le paramétre pour savoir si on lance la decompression ou la compression 
                                                                                                                                         
def choix():                                                                                                                            
      print "BIENVENUE DANS LE PROGRAMME DE TRIS'n CHRIS, Que voulez vous faire ?"
      print " rentrez d pour decompresser ou c pour compresser "                                                                                                                                                                           # parametre rentré est bien le bon 
                                                                                                                                                                  
      
      global res
      res=raw_input()
      
      while not res=="d" and not res=="c" :
            print " vous n'avez pas entré le bon paramètre "
            print"                    recommencez                         "
            res=raw_input()
      if res=="d":
            print "vous avez choisit la decompression"
            print "lancement"
            
      else :
            print " Vous avez choisi la compression"
            print "lancement"
            



            
#2 fonction qui demande le chemin du fichier et qui va ensuite lancer le
            #decompresseur sur tout les fichier trouvés dans son arborescence
                                                                                                                                                #ou du dossier a compresser 
   
def compression():
      cpt=0
      extensions={} 
      if res=="c":
       temp()
       print  "  Vous etes dans le compresseur "
       print  "  Entrez un chemin contenant les fichiers textes a compresser : "
       chemin=raw_input()
       while not os.path.isdir(chemin) and not os.path.isfile(chemin) :
             print"Votre chemin est mal ecrit ou n'existe pas réessesyez : "
             chemin=raw_input()
       print"votre chemin est donc :"
       print  chemin
     

                                                                                                                                                 #parcours des repertoire a la recherche
                                                                                                                                                      # de fichier texte
       def parcours (repertoire,niveau) :
          liste=os.listdir(repertoire)
          for fichier in liste :
              if os.path.isdir(repertoire+"/"+fichier) :
                 parcours(repertoire+"/"+fichier, niveau+1)
              else :
                    ext=re.search("(.+)\.(.*)",fichier)
                    if ext.group(2) == "txt" :
                       extensions[fichier]=repertoire+"/"+fichier
                       
       parcours(chemin,0)
       

     
              

 #os.chdir("/home/matthias/Documents/huff")
       count=0
       for elt in extensions:#################################################### A-1 je fais un gros fichier texte avec tout les fichier
                                                                            #texte trouver a partire de chemin
            '''sep=open("sep.txt","w")
            listesep=open("listesep.txt","a")
            sep.write(elt)
            listesep.write(elt+"\n")
            #sep.close()
            listesep.close()'''
            os.system("./huf "+extensions[elt]+" compresser/"+elt)
            #global extens
            #extens[elt]="home/matthias/Documents/final/compresser/"+elt
            print"compression de/ "+elt
            
            
            
            #os.system("cat compresser.txt >> toto.txt")
            #os.system("cat toto.txt >> gros.txt")
            '''os.remove("compresser.txt")
            os.remove("sep.txt")
            os.remove("toto.txt")'''
            
       
    
######################################################################################   partie decompression

def decompress():
  if res=='d':
    temp()
    print"Vous etes dans le decompresseur"
    print"Venez vous de compresser un fichier ? (oui ou non)"
    reponse=raw_input()
    while not reponse=="oui" and not reponse=="non" :
        print "Je ne comprends pas votre reponse veuillez la ressaisire :"
        reponse=raw_input()
    if reponse=="oui":
          print"Voulez vous decompresser le fichier que vous venez de compressez ? (oui ou non)"
          reponse=raw_input()
          while not reponse=="oui" and not reponse=="non" :
              print "je ne comprends pas votre reponse veuillez la ressaisire :"
              reponse=raw_input()
          
          if reponse=="oui":
                chemino="compresser/"
                liste=os.listdir(chemino)
                
                for fichier in liste :
                   print fichier
                   os.system("./dehuf compresser/"+fichier+"  decompresser/"+fichier)
                   os.remove("compresser/"+fichier)
            
                       

               
          
          












          '''fi=open('gros.txt','r')
          laligne=open('decomp.txt',"w")
          
          ligne=fi.readline()
          for ligne in fi:
                nomfichier=re.search("(.+)(\.)(.*)",ligne)
                if not nomfichier.group(3)=='txt':
                  
                     
                 laligne.write(ligne)
                                    
                 
                      
                fi.close()
                laligne.close()
                os.system("cat decomp.txt  >> /home/matthias/Documents/final/essai/essai.txt")'''
                

          






fin="a"  #boucle pour lancer le programme 
while not fin=="oui" :

      choix()
      compression()
      decompress()
      print"voulez-vous quitter le programme ?(oui ou non)"
      fin=raw_input()
      if fin=="non":
            print " Le programme se relance patientez " 
            temp()




      
      
  

      
                
                
    
  
     
   

