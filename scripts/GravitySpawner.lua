GravitySpawner = {
	fireTime = 60, --200
	postMoveTime = 20,
	fill = Color.new(128, 128, 128),
	postMoveFill = Color.new(47, 79, 79)
}

GravitySpawner.EnemyInstanceVars = {
	alpha = 194,
	stopped = false,
	grown = false,
	movingCircleRadius = 50
}

function GravitySpawner.EnemyInstanceVars:new(o)
	o = o or {}
	setmetatable(o, self)
	self.__index = self
	return o
end

function GravitySpawner.spawnEnemies(spawner)
	e = Enemy.new(spawner.position.x - 6.5, spawner.position.y + 20, 0.0, 2.0, 100000000, Color.new(128, 128, 128, 194))
	e.size.x = 30
	e.size.y = 30
	e.position.x = (spawner.position.x + 8) - (e.size.x / 2)
	e:setFatal(false)
	return {
		amount = 1,
		enemies = {
			e
		}
	}
end

function GravitySpawner.enemyUpdate(enemy, environment)
	enemy.instanceVars.alpha = enemy.instanceVars.alpha - 6
	if enemy.instanceVars.alpha < 0 then
		enemy.instanceVars.alpha = 0
	end
	enemy.fill = Color.new(128, 128, 128, enemy.instanceVars.alpha)

	if enemy.instanceVars.stopped then
		enemy.size.x = enemy.size.x + 4
		enemy.position.x = enemy.position.x - 2
		enemy.size.y = enemy.size.y + 4
		enemy.position.y = enemy.position.y - 2
		if enemy.size.x >= 100 then
			enemy.size.x = 100
			enemy.position.x = enemy.position.x + 2
			enemy.size.y = 100
			enemy.position.y = enemy.position.y + 2
			enemy.instanceVars.grown = true
		end
		enemy.position.y = enemy.position.y - enemy.velocity.y
		enemy.instanceVars.alpha = 194

		pcx = environment.player.position.x + 10
		pcy = environment.player.position.y + 10
		ecx = enemy.position.x + (enemy.size.x / 2)
		ecy = enemy.position.y + (enemy.size.y / 2)
		if pcx > ecx then
			environment.player.position.x = environment.player.position.x - 1.5
		else
			environment.player.position.x = environment.player.position.x + 1.5
		end

		if pcy > ecy then
			environment.player.position.y = environment.player.position.y - 1.5
		else
			environment.player.position.y = environment.player.position.y + 1.5
		end

		enemy.instanceVars.movingCircleRadius = enemy.instanceVars.movingCircleRadius - 1
		if enemy.instanceVars.movingCircleRadius == 1 then
			enemy.instanceVars.movingCircleRadius = 50
		end
	end

	if floatRectHitTest(environment.player:bounds(), enemy:bounds()) then
		enemy.instanceVars.stopped = true
		enemy.instanceVars.alpha = 194
	elseif enemy.size.x > 20 then
		enemy.instanceVars.stopped = false
		enemy.size.x = enemy.size.x - 4
		enemy.position.x = enemy.position.x + 2
		enemy.size.y = enemy.size.y - 4
		enemy.position.y = enemy.position.y + 2
		enemy.instanceVars.alpha = 194
		enemy.instanceVars.grown = false
	end
end

function GravitySpawner.enemyRender(enemy, window)
	circle = Circle.new(enemy.size.x / 2)
	setCirclePosition(circle, enemy.position.x, enemy.position.y)
	if not enemy.instanceVars.stopped then
		circle:setFill(enemy.fill)
	else
		circle:setFill(Color.new(255, 255, 255, 0))
		circle:setBorder(enemy.fill)
		circle:setBorderWidth(7.0)
		
		innerDot = Circle.new(5)
		setCirclePosition(innerDot, (enemy.position.x + (enemy.size.x / 2.0)) - 5.0, (enemy.position.y + (enemy.size.y / 2.0)) - 5.0)
		innerDot:setFill(enemy.fill)
		draw(window, innerDot)

		if enemy.instanceVars.grown then
			movingCircle = Circle.new(enemy.instanceVars.movingCircleRadius)
			setCirclePosition(movingCircle, (enemy.position.x + (enemy.size.x / 2.0)) - enemy.instanceVars.movingCircleRadius, (enemy.position.y + (enemy.size.y / 2.0)) - enemy.instanceVars.movingCircleRadius)
			movingCircle:setFill(Color.new(255, 255, 255, 0))
			movingCircle:setBorder(enemy.fill)
			movingCircle:setBorderWidth(4.0)
			draw(window, movingCircle)
		end
	end
	draw(window, circle)
end