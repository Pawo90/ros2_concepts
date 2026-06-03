/**
 * Simple ROS2 Subscriber Example
 *
 * This node subscribes to the '/number' topic and
 * prints received integer values.
 */

// ROS2 C++ client library
#include "rclcpp/rclcpp.hpp"

// Standard ROS2 message type for 64-bit integers
#include "std_msgs/msg/int64.hpp"

using std::placeholders::_1;

/**
 * A simple ROS2 subscriber node.
 *
 * This node listens to the '/number' topic and
 * displays received integer messages.
 */

class SimpleSubscriberNode : public rclcpp::Node 
{
public:
	/**
	 *  Initialize the subscriber node and topic subscription.
	 */
	SimpleSubscriberNode() : Node("simple_subscriber")
	{	
		// Create a subscriber
        //
        // Parameters:
        // - Message type: Int64
        // - Topic name: "/number"
        // - Callback function: subscriber_callback
        // - Queue size: 10
		number_subscriber_ = this->create_subscription<std_msgs::msg::Int64>(
			"/number",
			10,
			std::bind(&SimpleSubscriberNode::subscriber_callback, this, _1)
		);

		// Display startup message in ROS2 logs
		RCLCPP_INFO(this->get_logger(), "Simple C++ subscriber node has been started");
	}
private:

    /**
     * Callback function triggered on every received message.
     * Prints the received integer value to ROS2 logs.
     *
     * @param msg Shared pointer to the received Int64 message
     */
	void subscriber_callback(const std_msgs::msg::Int64::SharedPtr msg)
	{
		// Display received value in ROS2 logs
		RCLCPP_INFO(this->get_logger(), "Received data: %ld", msg->data);
	}

	// Subscriber handle for the '/number' topic
	rclcpp::Subscription<std_msgs::msg::Int64>::SharedPtr number_subscriber_;
};

/**
 * Main function responsible for node initialization
 * and execution.
 */
int main(int argc, char **argv)
{	
	// Initialize ROS2 communication
	rclcpp::init(argc, argv);

	// Create node instance
	auto node = std::make_shared<SimpleSubscriberNode>();
	
	// Keep the node running
	rclcpp::spin(node);

	// Shutdown ROS2 when execution ends
	rclcpp::shutdown();
	return 0;
} 