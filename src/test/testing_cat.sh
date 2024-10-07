#!/bin/bash

array=("A" "b" "Ab" "e" "Ae" "be" "Abe" "E" "AE" "bE" "AbE" "eE" "AeE" "beE" "AbeE" "n" "An" "bn" "Abn" "en" "Aen" "ben" "Aben" "En" "AEn" "bEn" "AbEn" "eEn" "AeEn" "beEn" "AbeEn" "s" "As" "bs" "Abs" "es" "Aes" "bes" "Abes" "Es" "AEs" "bEs" "AbEs" "eEs" "AeEs" "beEs" "AbeEs" "ns" "Ans" "bns" "Abns" "ens" "Aens" "bens" "Abens" "Ens" "AEns" "bEns" "AbEns" "eEns" "AeEns" "beEns" "AbeEns" "t" "At" "bt" "Abt" "et" "Aet" "bet" "Abet" "Et" "AEt" "bEt" "AbEt" "eEt" "AeEt" "beEt" "AbeEt" "nt" "Ant" "bnt" "Abnt" "ent" "Aent" "bent" "Abent" "Ent" "AEnt" "bEnt" "AbEnt" "eEnt" "AeEnt" "beEnt" "AbeEnt" "st" "Ast" "bst" "Abst" "est" "Aest" "best" "Abest" "Est" "AEst" "bEst" "AbEst" "eEst" "AeEst" "beEst" "AbeEst" "nst" "Anst" "bnst" "Abnst" "enst" "Aenst" "benst" "Abenst" "Enst" "AEnst" "bEnst" "AbEnst" "eEnst" "AeEnst" "beEnst" "AbeEnst" "T" "AT" "bT" "AbT" "eT" "AeT" "beT" "AbeT" "ET" "AET" "bET" "AbET" "eET" "AeET" "beET" "AbeET" "nT" "AnT" "bnT" "AbnT" "enT" "AenT" "benT" "AbenT" "EnT" "AEnT" "bEnT" "AbEnT" "eEnT" "AeEnT" "beEnT" "AbeEnT" "sT" "AsT" "bsT" "AbsT" "esT" "AesT" "besT" "AbesT" "EsT" "AEsT" "bEsT" "AbEsT" "eEsT" "AeEsT" "beEsT" "AbeEsT" "nsT" "AnsT" "bnsT" "AbnsT" "ensT" "AensT" "bensT" "AbensT" "EnsT" "AEnsT" "bEnsT" "AbEnsT" "eEnsT" "AeEnsT" "beEnsT" "AbeEnsT" "tT" "AtT" "btT" "AbtT" "etT" "AetT" "betT" "AbetT" "EtT" "AEtT" "bEtT" "AbEtT" "eEtT" "AeEtT" "beEtT" "AbeEtT" "ntT" "AntT" "bntT" "AbntT" "entT" "AentT" "bentT" "AbentT" "EntT" "AEntT" "bEntT" "AbEntT" "eEntT" "AeEntT" "beEntT" "AbeEntT" "stT" "AstT" "bstT" "AbstT" "estT" "AestT" "bestT" "AbestT" "EstT" "AEstT" "bEstT" "AbEstT" "eEstT" "AeEstT" "beEstT" "AbeEstT" "nstT" "AnstT" "bnstT" "AbnstT" "enstT" "AenstT" "benstT" "AbenstT" "EnstT" "AEnstT" "bEnstT" "AbEnstT" "eEnstT" "AeEnstT" "beEnstT" "AbeEnstT" "v" "Av" "bv" "Abv" "ev" "Aev" "bev" "Abev" "Ev" "AEv" "bEv" "AbEv" "eEv" "AeEv" "beEv" "AbeEv" "nv" "Anv" "bnv" "Abnv" "env" "Aenv" "benv" "Abenv" "Env" "AEnv" "bEnv" "AbEnv" "eEnv" "AeEnv" "beEnv" "AbeEnv" "sv" "Asv" "bsv" "Absv" "esv" "Aesv" "besv" "Abesv" "Esv" "AEsv" "bEsv" "AbEsv" "eEsv" "AeEsv" "beEsv" "AbeEsv" "nsv" "Ansv" "bnsv" "Abnsv" "ensv" "Aensv" "bensv" "Abensv" "Ensv" "AEnsv" "bEnsv" "AbEnsv" "eEnsv" "AeEnsv" "beEnsv" "AbeEnsv" "tv" "Atv" "btv" "Abtv" "etv" "Aetv" "betv" "Abetv" "Etv" "AEtv" "bEtv" "AbEtv" "eEtv" "AeEtv" "beEtv" "AbeEtv" "ntv" "Antv" "bntv" "Abntv" "entv" "Aentv" "bentv" "Abentv" "Entv" "AEntv" "bEntv" "AbEntv" "eEntv" "AeEntv" "beEntv" "AbeEntv" "stv" "Astv" "bstv" "Abstv" "estv" "Aestv" "bestv" "Abestv" "Estv" "AEstv" "bEstv" "AbEstv" "eEstv" "AeEstv" "beEstv" "AbeEstv" "nstv" "Anstv" "bnstv" "Abnstv" "enstv" "Aenstv" "benstv" "Abenstv" "Enstv" "AEnstv" "bEnstv" "AbEnstv" "eEnstv" "AeEnstv" "beEnstv" "AbeEnstv" "Tv" "ATv" "bTv" "AbTv" "eTv" "AeTv" "beTv" "AbeTv" "ETv" "AETv" "bETv" "AbETv" "eETv" "AeETv" "beETv" "AbeETv" "nTv" "AnTv" "bnTv" "AbnTv" "enTv" "AenTv" "benTv" "AbenTv" "EnTv" "AEnTv" "bEnTv" "AbEnTv" "eEnTv" "AeEnTv" "beEnTv" "AbeEnTv" "sTv" "AsTv" "bsTv" "AbsTv" "esTv" "AesTv" "besTv" "AbesTv" "EsTv" "AEsTv" "bEsTv" "AbEsTv" "eEsTv" "AeEsTv" "beEsTv" "AbeEsTv" "nsTv" "AnsTv" "bnsTv" "AbnsTv" "ensTv" "AensTv" "bensTv" "AbensTv" "EnsTv" "AEnsTv" "bEnsTv" "AbEnsTv" "eEnsTv" "AeEnsTv" "beEnsTv" "AbeEnsTv" "tTv" "AtTv" "btTv" "AbtTv" "etTv" "AetTv" "betTv" "AbetTv" "EtTv" "AEtTv" "bEtTv" "AbEtTv" "eEtTv" "AeEtTv" "beEtTv" "AbeEtTv" "ntTv" "AntTv" "bntTv" "AbntTv" "entTv" "AentTv" "bentTv" "AbentTv" "EntTv" "AEntTv" "bEntTv" "AbEntTv" "eEntTv" "AeEntTv" "beEntTv" "AbeEntTv" "stTv" "AstTv" "bstTv" "AbstTv" "estTv" "AestTv" "bestTv" "AbestTv" "EstTv" "AEstTv" "bEstTv" "AbEstTv" "eEstTv" "AeEstTv" "beEstTv" "AbeEstTv" "nstTv" "AnstTv" "bnstTv" "AbnstTv" "enstTv" "AenstTv" "benstTv" "AbenstTv" "EnstTv" "AEnstTv" "bEnstTv" "AbEnstTv" "eEnstTv" "AeEnstTv" "beEnstTv" "AbeEnstTv")
filename="testing.txt"

for ((i = 0; i < 511; i++))
do
    option=${array[i]}
    # echo "${array[i]} test $i"
    result="$(diff <(cat -"$option" "$filename") <(./../cat/s21_cat -"$option" "$filename"))"
    if [ -z "$result" ]
    then
        echo "test $i succeeded "${array[i]}""
    else
        echo "${array[i]} test $i failed"
        echo "$result"
    fi
done

result="$(diff <(cat "$filename") <(./../cat/s21_cat "$filename"))"
if [ -z "$result" ]
then
    echo "simple test is ok"
else
    echo "${array[i]} test $i failed"
    echo "$result"
fi