#!/bin/bash

# change video speed
# speed up
ffmpeg -i input.mkv -filter_complex "[0:v]setpts=0.5*PTS[v];[0:a]atempo=2.0[a]” -map "[v]" -map "[a]" output.mkv

# slow down
ffmpeg -i input.mkv -filter_complex "[0:v]setpts=2*PTS[v];[0:a]atempo=0.5[a]” -map "[v]" -map "[a]" output.mkv


# reverse

ffmpeg -i output_5.mp4 -vf reverse -af areverse output_5_r.mp4


# video-audio async fix

ffmpeg -i casey_final.mp4 -vf setdar=1/1 -video_track_timescale 29971 -ac 1 new2_casey.mp4


# overlay

ffmpeg -i s_e2.mp4 -i output_6.mp4 -filter_complex "[0:v]setpts=PTS-STARTPTS[v0];[1:v]setpts=PTS-STARTPTS+26/TB[v1];[v0][v1]overlay=eof_action=pass[out1]" -map [out1]  s_e3.mp4


#add audio from another video
#audio from source video

ffmpeg -i s_e3.mp4 -i output_75new.mp4 -c copy -map 0:0 -map 1:1 -shortest s_f2.mp4


# rescale video size

ffmpeg -i s_final.mp4 -vf “scale=1440x810” output1440.mp4


# padding video to a certain size

ffmpeg -i output_1600.mp4 -vf "pad=width=1920:height=1920:x=160:y=510:color=black" s_final_1920.mp4
