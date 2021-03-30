#include "include/main.hpp"

// Global variables
std::list <GameObject *> *gameObjects = new std::list <GameObject *>();
std::list <PlayerShipShot *> *playerShipShots = new std::list <PlayerShipShot *>();
bool stopAnim = true;

BasicFighter *playerShip = new BasicFighter(0.0, 0.0, 0.1, 0.1, false, 100);

// Main function
int main(){
    const int width = 1024; 
    const int height = 1024;

    std::pair<uint8_t, uint8_t> glVersion(4, 6);
    
    if (glfwInit()){
        std::cout << "GLFW LIBRARY INITIALIZATION STATUS... [OK]\n";
    }
    else{
        throw std::runtime_error("ERROR: Failed to initialize GLFW");
    }

    Window mainWindow(width, height, "OGL PROJECT");
    mainWindow.set_current();
    mainWindow.show();

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glVersion.first);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glVersion.second);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
	
    if (glewInit() != GLEW_OK) {
		throw std::runtime_error("ERROR: Failed to initialize GLEW");
	}
    else{
        std::cout << "GLEW LIBRARY INITIALIZATION STATUS... [OK]\n";
    }
    

    glfwSetInputMode(mainWindow.getContext(), GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.0f, 0.043f, 0.145f, 0.0f);
    glfwSetKeyCallback(mainWindow.getContext(), keyCallback);
    glfwSetMouseButtonCallback(mainWindow.getContext(), mouseCallback);
    glfwSetWindowSizeCallback(mainWindow.getContext(), resizeCallback);
    
    glScalef(height/(float)width, 1, 1);

    playerShip->speed = 0.035;

    // Main loop
    while(true){
      glClear(GL_COLOR_BUFFER_BIT);

      std::list<GameObject*>::iterator gameObject = gameObjects->begin(); 
      std::list<PlayerShipShot*>::iterator shotObject = playerShipShots->begin();

      playerShip->update(mainWindow.getContext());

      if(stopAnim == false){

          while (gameObject != gameObjects->end()){
        bool collided = false;

        shotObject = playerShipShots->begin();
        while (shotObject != playerShipShots->end())
        {
          if(isCollided(*shotObject, *gameObject)){
              collided = true;
              (*playerShipShots).erase(shotObject++);
              break;
          }
          ++shotObject;
        }
        
        
        if((*gameObject)->yBias < -2.8 || collided == true){
          (*gameObjects).erase(gameObject++);
        }
        else{
          (*gameObject)->update(mainWindow.getContext());
          ++gameObject;
        }
      }
      
          shotObject = playerShipShots->begin();
          while (shotObject != playerShipShots->end()){
        
        if((*shotObject)->yBias > 2.4){
          (*playerShipShots).erase(shotObject++);
        }
        else{
          (*shotObject)->update(mainWindow.getContext());
          ++shotObject;
        }
      }
      
          playerShip->update(mainWindow.getContext());

          glfwSwapBuffers(mainWindow.getContext());
      }
      
      glfwPollEvents();
      glfwSwapBuffers(mainWindow.getContext()); // !!!REMOVE THIS!!!
      if(glfwWindowShouldClose(mainWindow.getContext()) != 0){
        break;
      }

      if(getRandom(0, 1000) > 970 && stopAnim == false){
        int choosenObject = getRandom(0, 9);
        if(choosenObject <= 8){
          
          double innerRadius = getRandom(0.02, 0.08);
          SpikeObject *spike = new SpikeObject(getRandom(-0.9, 0.9), 1.5, innerRadius, 
                      getRandom(innerRadius, innerRadius*3), 0.5, getRandom(0.005, 0.02));


          gameObjects->push_back(spike);
        }
        else if(choosenObject > 8){
          TieFighter *tieFighter = new TieFighter(getRandom(-0.9, 0.9), 1.5, 0.02, 0.12, getRandom(0.005, 0.02));

          gameObjects->push_back(tieFighter);
        }
      }
      
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }

    return 0;
}