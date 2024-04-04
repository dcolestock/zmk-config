#!/usr/bin/env bash
set -e

echo "Pushing..."
git push
RUNID=$(gh run list --json databaseId -q '.[0]'.databaseId)
echo "Watching..."
gh run watch $RUNID --exit-status
echo "Viewing..."
gh run view $RUNID
echo "Downloading..."
OUTDIR=output_images/$(date +"%Y.%m.%d_%H.%M.%S")
gh run download $RUNID -D $OUTDIR

MOUNTFOLDER=/run/media/dan/NICENANO

#Left Board
echo Bootloader left board
while [ ! -d $MOUNTFOLDER ]; do
  sleep 0.5
done
echo Copy Started...
cp $OUTDIR/firmware/*left*.uf2 $MOUNTFOLDER
echo Copy Complete!

#Right Board
echo Bootloader right board
while [ ! -d $MOUNTFOLDER ]; do
  sleep 0.5
done
echo Copy Started...
cp $OUTDIR/firmware/*right*.uf2 $MOUNTFOLDER
echo Copy Complete!
