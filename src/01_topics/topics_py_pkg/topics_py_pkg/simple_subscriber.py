#!/usr/bin/env python3

"""
Simple ROS2 Subscriber Example

This node subscribes to the '/number' topic and
prints received integer values.
"""

# ROS2 Python client library
import rclpy
from rclpy.node import Node

# Standard ROS2 message type for 64-bit integers
from std_msgs.msg import Int64


class SimpleSubscriberNode(Node):
    """
    A simple ROS2 subscriber node.

    This node listens to the '/number' topic and
    displays received integer messages.
    """

    def __init__(self):
        """
        Initialize the subscriber node and topic subscription.
        """
        # Initialize the ROS2 node with the name 'simple_subscriber'
        super().__init__('simple_subscriber')

        # Create a subscriber
        #
        # Parameters:
        # - Message type: Int64
        # - Topic name: "/number"
        # - Callback function: subscriber_callback
        # - Queue size: 10
        self.number_subscriber_ = self.create_subscription(
            Int64,
            "/number",
            self.subscriber_callback,
            10
        )

        # Display startup message in ROS2 logs
        self.get_logger().info(
            "Simple Python subscriber node has been started"
        )

    def subscriber_callback(self, msg: Int64):
        """
        Callback function executed whenever
        a new message is received.
        """
        # Print received value to ROS2 logs
        self.get_logger().info(
            f"Received data: {msg.data}"
        )


def main(args=None):
    """
    Main function responsible for node initialization
    and execution.
    """
    # Initialize ROS2 communication
    rclpy.init(args=args)

    # Create node instance
    node = SimpleSubscriberNode()

    # Keep the node running and processing callbacks
    rclpy.spin(node)

    # Shutdown ROS2 when execution ends
    rclpy.shutdown()


if __name__ == '__main__':
    main()