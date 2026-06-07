import rclpy
import time
from rclpy.node import Node
from rclpy.action import ActionServer, GoalResponse
from rclpy.action.server import ServerGoalHandle

from example_interfaces.action import Fibonacci

class SimpleActionServerNode(Node):
	def __init__(self):
		super().__init__('simple_action_server_node')
		
		# Create an action server
		# Parameters:
		# - Interface type: Fibonacci
		# - Action name: "/fibonacci"
		# - Callback function: goalCallback
		# - Execute callback function: executeCallback
		self.action_server_ = ActionServer(
			self,
			Fibonacci,
			'/fibonacci',
			goal_callback=self.goalCallback,
			execute_callback=self.executeCallback
		)

		self.get_logger().info(
			"Simple Python action server node has been started"
		)
		
	# Callback triggered when the client sends a new goal request.
	# Validates the request and decides whether to accept or reject it.
	# Returns GoalResponse.ACCEPT or GoalResponse.REJECT.
	def goalCallback(self, goal_request: Fibonacci.Goal):
		self.get_logger().info("Received a goal")
		
		if goal_request.order <= 2:
			self.get_logger().warn(
				"Rejecting the goal, order number must be >= 2")
			return GoalResponse.REJECT
		
		self.get_logger().info("Accepting the goal")
		return GoalResponse.ACCEPT
		
	# Callback triggered once the goal is accepted – this is where
	# the action is actually executed. On each loop iteration:
	# - checks if the client has requested cancellation,
	# - computes the next Fibonacci number in the sequence,
	# - publishes feedback with the current partial sequence.
	# Once the loop finishes, marks the goal as succeeded and returns the result
	def executeCallback(self,  goal_handle: ServerGoalHandle):
		target_order = goal_handle.request.order
		
		# FEEDBACK - Optional
		feedback = Fibonacci.Feedback()
		
		sequence = [0, 1]
		self.get_logger().info('Executing goal...')
		
		for i in range(1, target_order):
			# CANCEL - Optional
			# Check if there is a cancel request
			if goal_handle.is_cancel_requested:
				goal_handle.canceled()
				self.get_logger().info('Goal canceled')
				return Fibonacci.Result()
		
			sequence.append(sequence[i] + sequence[i-1])
			
			# FEEDBACK - Optional publish
			feedback.sequence = sequence
			goal_handle.publish_feedback(feedback)
			self.get_logger().info(f'Publishing feedback: {feedback}')
			time.sleep(1)

		# If goal is done	
		goal_handle.succeed()
		result = Fibonacci.Result()
		result.sequence = sequence
		
		return result

		
def main(args=None):
	rclpy.init(args=args)
	node = SimpleActionServerNode()
	rclpy.spin(node)
	rclpy.shutdown()
  

if __name__ == '__main__':
	main()