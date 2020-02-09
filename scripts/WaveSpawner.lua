WaveSpawner = {
	fireTime = 400,
	fill = Color.new(0, 0, 255),
	warningFireFill = Color.new(0, 206, 209)
}

function WaveSpawner.spawnEnemies(spawner)
	return {
		amount = 1,
		enemies = {
			Enemy.new(spawner.position.x + 3, spawner.position.y + 20, 0.0, 2.0, 300, Color.new(0, 0, 0))
		}		
	}
end

ec = 0
function WaveSpawner.spawnerUpdate(spawner, environment)
	if not spawner.moving then
		return
	end
	if ec > 10 then
		e = Enemy.new(spawner.position.x + 3, spawner.position.y + 20, 0.0, 2.0, 300, Color.new(0, 0, 0))
		environment:addEnemy(e, "WaveSpawner")
		ec = 0
	end
	ec = ec + 1
end