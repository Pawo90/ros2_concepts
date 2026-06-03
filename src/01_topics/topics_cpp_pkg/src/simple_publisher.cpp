/**
 * Simple ROS2 Publisher Example
 *
 * This node publishes incrementing integer values
 * to the '/number' topic every second.
 */

// ROS2 C++ client library
#include "rclcpp/rclcpp.hpp"

// Standard ROS2 message type for 64-bit integers
#include "std_msgs/msg/int64.hpp"


/**
 * A simple ROS2 publisher node.
 *
 * This node publishes incrementing integer values to the
 * '/number' topic once every second.
 */
class SimplePublisherNode : public rclcpp::Node
{
public:
	/**
	 * Initialize the publisher node, topic, and timer.
	 */
	SimplePublisherNode() : Node("simple_publisher")
	{
		// Create a publisher
		//
		// Parameters:
		// - Message type: Int64
		// - Topic name: "/number"
		// - Queue size: 10
		number_publisher_ = this->create_publisher<std_msgs::msg::Int64>(
			"/number",
			10
		);

		// Create a timer that triggers every 1 second
		// and calls the publish_number() callback function
		publish_timer_ = this->create_timer(
			std::chrono::seconds(1),
			std::bind(&SimplePublisherNode::publish_number, this)
		);

		// Display startup message in ROS2 logs
		RCLCPP_INFO(this->get_logger(), "Simple C++ publisher node has been started");
	}

private:

	/**
	 * Create and publish a message containing
	 * the current counter value.
	 */
	void publish_number()
	{
		// Create a new Int64 message object
		auto msg = std_msgs::msg::Int64();

		// Assign current counter value to the message
		msg.data = number_;

		// Publish the message to the topic
		number_publisher_->publish(msg);

		// Increment counter for the next publication
		number_ += 1;
	}

	// Internal counter value to be published
	int64_t number_ = 0;

	// Publisher handle for the '/number' topic
	rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr number_publisher_;

	// Timer handle triggering publish_number() every second
	rclcpp::TimerBase::SharedPtr publish_timer_;
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
	auto node = std::make_shared<SimplePublisherNode>();

	// Keep the node running
	rclcpp::spin(node);

	// Shutdown ROS2 when execution ends
	rclcpp::shutdown();
	return 0;
}