#!/usr/bin/env python3

"""
Simple ROS2 Publisher Example

This node publishes incrementing integer values
to the '/number' topic every second.
"""

# ROS2 Python client library
import rclpy
from rclpy.node import Node

# Standard ROS2 message type for 64-bit integers
from std_msgs.msg import Int64


class SimplePublisherNode(Node):
    """
    A simple ROS2 publisher node.

    This node publishes incrementing integer values to the
    '/number' topic once every second.
    """

    def __init__(self):
        """
        Initialize the publisher node, topic, and timer.
        """
        # Initialize the ROS2 node with the name 'simple_publisher'
        super().__init__('simple_publisher')

        # Internal counter value to be published
        self.number_ = 0

        # Create a publisher
        #
        # Parameters:
        # - Message type: Int64
        # - Topic name: "/number"
        # - Queue size: 10
        self.number_publisher_ = self.create_publisher(
            Int64,
            "/number",
            10
        )

        # Create a timer that triggers every 1 second
        # and calls the publish_number() callback function
        self.publish_timer_ = self.create_timer(
            1.0,
            self.publish_number
        )

        # Display startup message in ROS2 logs
        self.get_logger().info(
            "Simple Python publisher node has been started"
        )

    def publish_number(self):
        """
        Create and publish a message containing
        the current counter value.
        """
        # Create a new Int64 message object
        msg = Int64()

        # Assign current counter value to the message
        msg.data = self.number_

        # Publish the message to the topic
        self.number_publisher_.publish(msg)

        # Increment counter for the next publication
        self.number_ += 1


def main(args=None):
    """
    Main function responsible for node initialization
    and execution.
    """
    # Initialize ROS2 communication
    rclpy.init(args=args)

    # Create node instance
    node = SimplePublisherNode()

    # Keep the node running
    rclpy.spin(node)

    # Shutdown ROS2 when execution ends
    rclpy.shutdown()


if __name__ == '__main__':
    main()