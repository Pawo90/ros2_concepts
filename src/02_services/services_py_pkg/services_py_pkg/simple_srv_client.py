#!/usr/bin/env python3
import rclpy
from rclpy.node import Node


class SimpleServiceClient(Node): 
	def __init__(self):
		super().__init__('simple_service_client')

		self.add_ints_service_ = self.create_service()

		self.get_logger().info(
            "Simple Python service client node has been started"
        )


def main(args=None):
	rclpy.init(args=args)
	node = SimpleServiceClient()

	rclpy.spin(node)
	rclpy.shutdown()

if __name__ == '__main__':
	main()