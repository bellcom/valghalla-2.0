Valghalla - rekruttering af valgtilforordnede
-----------------------------
Valghalla er et webbaseret system til håndtering af valgstyrere og tilforordnede i forbindelse med valg. Løsningen er oprindeligt udviklet af Aarhus Kommune og gratis tilgængeligt for alle.

Valghalla er udviklet til at forenkle og digitalisere processen med at rekruttere tilforordnede til valg. Og så er den Open Source, så andre kommuner kan få glæde af den. Valghalla er et produkt der udvikles og vdeligeholdes af OS2. Se mere her: https://os2.eu/produkt/os2valghalla

De overordnede mål er:

* Digitalisere en tung, manuel opgave og bibeholde meget højt datasikkerhedsniveau
* Anvendelse af automatiserede e-mails, der hvor det er muligt
* Give valgsekretariatet i kommunen et simpelt overblik over en kompleks opgave
* Give partiforeningerne overblikket over deres andel af valget
* Mest mulig uddelegering ved at smidiggøre partiforeningernes opgave
* Størst mulig automatiseringsgrad af bekræftelser m.m.
* Hurtigere effektuering ved efterfølgende valg gennem genbrug af data

## Build status

Develop branch state ![alt text](https://travis-ci.org/bellcom/valghalla.svg?branch=develop)

## Deployment new changes

To deploy new changes and apply all deploy actions please use following steps. 

* Fetch new tags `git fetch origin 'refs/tags/*:refs/tags/*'`
* Checkout to tag you deploying `git checkout [tag name]`
* Switch to drupal root directory `cd public_html` 
* Run deployment script `sh ../scripts/deploy-multisite.sh`

Deployment output log will be saved to `logs/deployment/deployment-[date]-[time].log` file. 
