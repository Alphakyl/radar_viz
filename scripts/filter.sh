#!/bin/bash
files=/home/kyle/data/radar/icra/*
for file in $files
do
    echo "Existing file:"
    echo ${file%.bag}
    echo "New file:"
    echo ${file%_no_tfs.bag}
    echo "Filter:"
    rosbag filter ${file%.bag} ${file%_no_tfs.bag} "topic == 'imu_in/data' or topic == 'imu_out/data' or topic == 'os1_cloud_node/imu' or topic=='os1_cloud_node/points'"
    echo "Filtering complete."
done
echo "Done"