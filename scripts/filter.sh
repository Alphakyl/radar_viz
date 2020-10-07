#!/bin/bash
files=/home/kyle/data/radar/icra/icra2021_test_data/ICRA2021_test_data/*
for file in $files
do
    echo "Existing file:"
    echo ${file}
    echo "New file:"
    echo ${file%.bag}_no_tf.bag
    echo "Filter:"
    rosbag filter ${file} ${file%.bag}_no_tfs.bag "topic == '/imu_in/data' or topic == '/imu_out/data' or topic == '/os1_cloud_node/imu' or topic=='/os1_cloud_node/points'"
    echo "Filtering complete."
done
echo "Done"
