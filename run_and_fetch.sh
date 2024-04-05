#!/usr/bin/env bash
set -e

echo "Pushing..."
git push

COMMIT=$(git rev-parse HEAD)
mkdir -p output_images
OUTDIR=$(find output_images/ -maxdepth 1 -type d -name *$COMMIT)

if [[ -n "$OUTDIR" ]]; then
  echo "Using already downloaded folder $OUTDIR"
else
  for attempt in {1..5}; do
    RUNID=$(gh run list --json headSha,databaseId -q ".[] | select(.headSha == \"$COMMIT\") | .databaseId")
    if [[ -n "$RUNID" ]]; then
      echo "Located run_id: $RUNID"
      break
    fi
    sleep 2
    echo "Attempt $attempt: run_id not found yet, Retrying..."
  done

  if [[ -z "$RUNID" ]]; then
    echo "Error: Failed to find run_id for hash '$COMMIT' after 5 attempts."
    exit 1
  fi

  echo "Watching..."
  gh run watch $RUNID --exit-status
  echo "Viewing..."
  gh run view $RUNID
  echo "Downloading..."
  TEMPOUT=$(mktemp -d)
  OUTDIR=output_images/$(date +"%Y.%m.%d")_$COMMIT
  gh run download $RUNID -D $TEMPOUT
  mkdir -p $OUTDIR
  mv $TEMPOUT/firmware/* "$OUTDIR"
fi

MOUNTFOLDER=/run/media/dan/NICENANO

#Left Board
echo Bootloader left board
while [ ! -d $MOUNTFOLDER ]; do
  sleep 0.5
done
echo Copy Started...
cp $OUTDIR/*left*.uf2 $MOUNTFOLDER
echo Copy Complete!

#Right Board
echo Bootloader right board
while [ ! -d $MOUNTFOLDER ]; do
  sleep 0.5
done
echo Copy Started...
cp $OUTDIR/*right*.uf2 $MOUNTFOLDER
echo Copy Complete!
