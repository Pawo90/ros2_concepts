#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

#include "example_interfaces/action/fibonacci.hpp"

using Fibonacci = example_interfaces::action::Fibonacci;
using GoalHandleFibonacci = rclcpp_action::ServerGoalHandle<Fibonacci>;

using std::placeholders::_1;
using std::placeholders::_2;

class SimpleActionServerNode : public rclcpp::Node 
{
public:
	SimpleActionServerNode() : Node("simple_action_server_node") 
	{

        // Create an action server
		// Parameters:
		// - Interface type: Fibonacci
		// - Action name: "/fibonacci"
		// - Callback function: goalCallback
		// - Execute callback function: executeCallback
        action_server_ = rclcpp_action::create_server<Fibonacci>(
            this,
            "/fibonacci",
            std::bind(&SimpleActionServerNode::goalCallback, this, _1, _2),
            std::bind(&SimpleActionServerNode::cancelCallback, this, _1),
            std::bind(&SimpleActionServerNode::executeCallback, this, _1)
        );

        RCLCPP_INFO(this->get_logger(), "Simple C++ action server node has been started");


	}
private:

    // Callback triggered when the client sends a new goal request.
	// Validates the request and decides whether to accept or reject it.
	// Returns GoalResponse.ACCEPT or GoalResponse.REJECT.
    rclcpp_action::GoalResponse goalCallback(
        const rclcpp_action::GoalUUID &uuid,
        std::shared_ptr<const Fibonacci::Goal> goal
    )
    {
        RCLCPP_INFO(this->get_logger(), "Received a goal");

        if (goal->order <= 2)
        {
            RCLCPP_WARN(this->get_logger(), "Rejecting the goal, order number must be >= 2");
            return rclcpp_action::GoalResponse::REJECT;
        };

        RCLCPP_INFO(this->get_logger(), "Accepting the goal");
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
        
    }

    // Cancell callback
    rclcpp_action::CancelResponse cancelCallback(
        const std::shared_ptr<GoalHandleFibonacci> goal_handle
    )
    {
        RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");
        (void)goal_handle;
        return rclcpp_action::CancelResponse::ACCEPT;
    }


    // Callback triggered once the goal is accepted – this is where
	// the action is actually executed. On each loop iteration:
	// - checks if the client has requested cancellation,
	// - computes the next Fibonacci number in the sequence,
	// - publishes feedback with the current partial sequence.
	// Once the loop finishes, marks the goal as succeeded and returns the result
    void executeCallback(const std::shared_ptr<GoalHandleFibonacci> goal_handle)
    {   
        rclcpp::Rate loop_rate(1.0);

        int32_t target_order = goal_handle->get_goal()->order;
        auto result = std::make_shared<Fibonacci::Result>();
        
        // FEEDBACK - Optional
        auto feedback = std::make_shared<Fibonacci::Feedback>();
        
        std::vector<int32_t> sequene = {0, 1};
        RCLCPP_INFO(this->get_logger(), "Executing goal...");

        for (int i =0; i < target_order; i++) {
            // CANCEL - Optional
			// Check if there is a cancel request
            if (goal_handle->is_canceling()) {
                result->sequence = sequene;
                goal_handle->canceled(result);
                RCLCPP_INFO(this->get_logger(), "Goal canceled");
                return;
            }

            sequene.push_back(sequene[i] + sequene[i - 1]);

            // FEEDBACK - Optional publish
            feedback->sequence = sequene;
            goal_handle->publish_feedback(feedback);
            std::string sequence_string;
            for (auto val : sequene) {
                sequence_string += std::to_string(val) + " ";
            }
            RCLCPP_INFO(this->get_logger(),
                "Publishing feedback: [%s]", sequence_string.c_str()
            );
           
            loop_rate.sleep();
        }

        // If goal is done
        result->sequence = sequene;      
        goal_handle->succeed(result);
        RCLCPP_INFO(this->get_logger(), "Goal succeeded");
    }


    // Action server handle for the '/fibonaci' action
    rclcpp_action::Server<Fibonacci>::SharedPtr action_server_;
};

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);
	auto node = std::make_shared<SimpleActionServerNode>(); 
	rclcpp::spin(node);
	rclcpp::shutdown();
	return 0;
} 