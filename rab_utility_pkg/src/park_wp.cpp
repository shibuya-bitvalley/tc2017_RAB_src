#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/transform_broadcaster.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

struct MyPose{
   double x;
   double y;
   double yaw;
};

int main(int argc, char** argv){
   // 起動後に10秒間スリープ
   ROS_INFO("waypoint launched! Wait 10 secs.");
   sleep(10);
   MyPose way_point[] = {
     {  4.226, -0.907,-0.281},
     {  7.041, -1.720,-0.194},
     { 10.789, -2.458,-0.169},
     { 13.660, -2.948,-0.237},
     { 16.498, -3.632,-0.308},
     { 19.414, -4.559,-0.344},
     { 22.409, -5.634,-0.097},
     { 24.201, -5.808,-0.107},
     { 27.331, -6.143,-0.181},
     { 30.067, -6.644,-0.004},
     { 33.042, -6.655,-0.191},
     { 35.999, -7.227,-0.096},
     { 39.121, -7.527,-0.188},
     { 42.465, -8.164,-0.136},
     { 45.438, -8.572,-0.158},
     { 48.443, -9.053,-0.222},
     { 52.100, -9.878,-0.073},
     { 55.150,-10.100,-0.169},
     { 58.246,-10.629,-0.097},
     { 62.295,-11.022,-0.067},
     { 65.164,-11.216,-0.081},
     { 68.111,-11.454,-0.045},
     { 70.219,-11.548, 0.742},
     { 71.439,-10.429, 1.071},
     { 72.019, -9.366, 1.389},
     { 72.498, -6.759, 1.454},
     { 72.857, -3.687, 1.460},
     { 73.045, -2.001, 1.420},
     { 73.841,  3.241, 1.357},
     { 74.466,  6.121, 1.713},
     { 73.906, 10.022, 1.507},
     { 74.141, 13.733, 1.142},
     { 75.466, 16.627, 1.437},
     { 76.084, 21.220, 2.430},
     { 73.972, 23.041, 2.171},
     { 72.298, 25.485, 1.605},
     { 72.155, 29.677, 1.799},
     { 71.505, 32.477, 1.851},
     { 70.921, 34.502, 2.757},
     { 67.382, 35.937, 3.035},
     { 64.269, 36.268, 3.049},
     { 60.446, 36.623, 3.040},
     { 57.556, 36.918, 3.103},
     { 54.786, 37.026, 3.097},
     { 51.624, 37.168, 3.110},
     { 48.520, 37.267, 3.124},
     { 44.634, 37.334, 3.071},
     { 41.661, 37.544, 3.132},
     { 37.750, 37.582, 3.080},
     { 34.104, 37.806, 3.094},
     { 30.071, 37.998, 3.083},
     { 27.113, 38.172, 3.052},
     { 23.843, 38.465, 3.116},
     { 21.114, 38.534,-3.111},
     { 18.311, 38.448,-3.082},
     { 14.856, 38.242, 3.124},
     { 12.060, 38.289, 3.129},
     {  8.913, 38.329,-3.082},
     {  5.894, 38.148,-3.139},
     {  2.856, 38.139,-3.117},
     { -0.878, 38.047, 3.119},
     { -2.895, 38.092,-3.132},
     { -6.021, 38.062,-3.093},
     { -8.899, 37.923, 3.083},
     {-10.950, 38.043,-3.094},
     {-12.924, 37.949, 3.090},
     {-14.866, 38.049, 3.014},
     {-18.017, 38.454,-3.067},
     {-20.991, 38.233, 3.085},
     {-25.068, 38.465,-3.133},
     {-28.027, 38.439, 3.116},
     {-31.001, 38.516, 3.040},
     {-33.891, 38.809, 2.905},
     {-35.772, 39.263, 2.200},
     {-36.847, 40.742, 1.513},
     {-36.662, 43.963, 1.559},
     {-36.638, 46.050, 1.567},
     {-36.630, 48.040, 1.554},
     {-36.579, 51.037, 1.529},
     {-36.472, 53.608, 1.613},
     {-36.551, 55.480, 1.550},
     {-36.464, 59.666, 1.534},
     {-36.391, 61.645, 1.534},
     {-36.355, 62.635, 1.533},
     {-36.253, 65.372, 1.614},
     {-36.419, 69.237, 1.562},
     {-36.400, 71.292, 1.696},
     {-36.640, 73.192, 1.547},
     {-36.569, 76.134,-1.123},
     {999, 999, 999}};
   ros::init(argc, argv, "wp_navigation");
   
   // アクションクライアンを作成。1番目の引数は接続するアクションサーバー名。          
   // ２番目の引数はtrueならスレッドを自動的に回す(ros::spin()。                       
   MoveBaseClient ac("move_base", true);
    
   // アクションサーバーが起動するまで待つ。引数はタイムアウトする時間(秒）。          
   // この例では５秒間待つ(ブロックされる)                                             
   while(!ac.waitForServer(ros::Duration(5.0))){
      ROS_INFO("Waiting for the move_base action server to come up");
   }
   
   ROS_INFO("The server comes up");
   move_base_msgs::MoveBaseGoal goal;
   // map(地図)座標系                             
   goal.target_pose.header.frame_id = "map";
   // 現在時刻                                                                         
   goal.target_pose.header.stamp = ros::Time::now();
      
   int i = 0;
   while (ros::ok()) {
      // ROSではロボットの進行方向がx座標、左方向がy座標、上方向がz座標                 
      goal.target_pose.pose.position.x =  way_point[i].x;
      goal.target_pose.pose.position.y =  way_point[i].y;
      
      if (goal.target_pose.pose.position.x == 999) break;
      
      goal.target_pose.pose.orientation
	= tf::createQuaternionMsgFromYaw(way_point[i].yaw);
      
      ROS_INFO("Sending goal: No.%d", i+1);
      // サーバーにgoalを送信                                                           
      ac.sendGoal(goal);
      
      // 結果が返ってくるまで60.0[s] 待つ。ここでブロックされる。                       
      bool succeeded = ac.waitForResult(ros::Duration(60.0));
      
      // 結果を見て、成功ならSucceeded、失敗ならFailedと表示                            
      actionlib::SimpleClientGoalState state = ac.getState();
      
      if(succeeded) {
	 ROS_INFO("Succeeded: No.%d (%s)",i+1, state.toString().c_str());
      }
      else {
	 ROS_INFO("Failed: No.%d (%s)",i+1, state.toString().c_str());
      }
      i++;
   }
   return 0;
}
