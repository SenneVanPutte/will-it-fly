# git-hulp

## Stap 0:

Maak een GitHub account aan, liefst met een duidelijke naam (bijvoorbeeld: Ivo Wingelaar, i.p.v. xxGundamDragonBallZSuperHeroFighter3000xx).

## Stap 1:

Zorg dat de configuratie van Git in orde is (gebruik uw eigen naam, in plaats van de mijne):

```
git config --global user.name "Ivo Wingelaar"
git config --global user.mail "ivo.wingelaar@student.uantwerpen.be"
```

Anders klaagt git.

## Stap 2:

Een goede workflow met Git, en onder andere GitHub, werkt met zogenaamde "forks". Een fork is een lokale kopie van de volledige repository waarin je write-permissions hebt. Write-permissions van de "hoofd" repository, ook wel "upstream" genoemd, blijven gereserveerd voor de administrators van het project (mijzelf, en misschien Andy, als ik hem vertrouw...).

Iedereen kan werken in zijn eigen fork. Ik zal de ontwikkeling van het project kunnen volgen, en iedereen zijn bijdrage kunnen "mergen" in de geschiedenis van upstream.

De repository van het project is:

```
https://github.com/3BaFys-2014-2015/will-it-fly.git
```

Ik vraag aan iedereen om deze repository te forken naar zijn eigen account (dit gebeurt rechtsboven in het venster van GitHub). Iedereen krijgt dan een kopie van de volledige repository in bijvoorbeeld:

```
https://github.com/IvoWingelaar/will-it-fly.git
```

Nu gaan we de repository "clone"en naar een directory op uw harde schijf (opnieuw uw eigen naam gebruiken, in plaats van de mijne):

```
mkdir eindwerk-programmeren
cd eindwerk-programmeren
git clone git@github.com:IvoWingelaar/will-it-fly.git
cd will-it-fly
```

Om updates van het hoofdproject te ontvangen, moet er ook een remote naar de originele repository gemaakt worden:

```
git remote add upstream https://github.com/3BaFys-2014-2015/will-it-fly.git
```

Nu is de volledige repository beschikbaar in "eindwerk-programmeren/will-it-fly", kijk maar eens! Alle git commando's worden best vanuit deze directory uitgevoerd.

## Stap 3:

Git is redelijk ingewikkeld, maar ik denk dat we er kunnen geraken als we ons gaan houden aan een aantal regels:

+ Iedereen werkt altijd in zijn eigen branch.
+ Vanaf dat iemand denkt klaar te zijn met zijn/haar opdracht: stuur mij (of Andy) een bericht op facebook, of een email.
+ Ik (of Andy) zal de code controleren, en deze na goedkeuring mergen in het hoofdproject.
+ De volledige geschiedenis van alles wordt dan op 1 centrale locatie opgeslagen.

## Stap 4:

De volgende workflow zal gehanteerd worden:

Na ontvangst van een opdracht, zal de persoon een nieuwe branch maken vanuit de master branch:

```
git checkout master
git pull upstream master
git checkout -b development-ivo-opdracht-1
git push --set-upstream origin development-ivo-opdracht-1
```

Nadat de branch is aangemaakt, verwacht ik dat ik de naam hiervan krijg, zodat ik ontwikkelingen kan volgen.

Als er bestanden worden aangemaakt, verwijderd of aangepast, moet git op de hoogte gebracht worden dat deze gevolgd moeten worden door het programma:

```
touch test.txt
git add test.txt
```

Als git de veranderingen in een bestand moet volgen, dan zegt men dat de file "gestaged" is. Een lijst van alle staged files is beschikbaar via

```
git status
```

Rode namen zijn niet staged, of zelfs niet een getracked. Om alle staged veranderingen te registreren in de repository, gebruik:

```
git commit -m "Commit message"
```

Vanaf nu zijn de veranderingen opgeslagen in de repository, en is het altijd mogelijk om terug te gaan naar dit punt in de geschiedenis. Gelieve een zinnige message toe te voegen, zodat iedereen weet wat dat commit precies inhoud:

```
echo "Tekst" >> file.txt
git add file.txt
git commit -m "Added file.txt"
```

Om de veranderingen in uw lokale repository te delen met de online repository, moet men de veranderingen uploaden met:

```
git pull
git push
```

Op dit moment zitten de veranderingen enkel in eigen fork! Ik moet zelf de veranderingen mergen in de hoofdrepository nadat ze zijn goedgekeurd. Hiervoor moet ik de branch naam weten.