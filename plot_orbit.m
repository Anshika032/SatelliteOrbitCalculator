function orbit_simulator()

% ================= LOAD DATA =================
data = readmatrix('orbit.csv');
x = data(:,1);
y = data(:,2);
v = data(:,3);

% ================= INITIAL SETTINGS =================
inclination = 45;
speed_factor = 1;
running = true;

% Apply inclination
y_new = y * cosd(inclination);
z = y * sind(inclination);
x_new = x;

% ================= FIGURE =================
fig = figure('Name','Orbit Simulator','NumberTitle','off');

% Plot orbit
plot3(x_new, y_new, z, 'b', 'LineWidth', 2)
hold on

% Earth
[Xs, Ys, Zs] = sphere(50);
earth_r = 6371;
surf(earth_r*Xs, earth_r*Ys, earth_r*Zs, ...
    'FaceColor','k','EdgeColor','none')

% Satellite
sat = plot3(x_new(1), y_new(1), z(1), ...
    'ro','MarkerFaceColor','r','MarkerSize',6);

axis equal
grid on
xlabel('X (km)')
ylabel('Y (km)')
zlabel('Z (km)')
title('🚀 Interactive Orbit Simulator')
legend('Orbit','Earth','Satellite')
view(3)
rotate3d on

% ================= UI CONTROLS =================

% Play/Pause Button
uicontrol('Style','pushbutton',...
    'String','Pause',...
    'Position',[20 20 80 30],...
    'Callback',@toggleRun);

% Speed Slider
uicontrol('Style','slider',...
    'Min',0.1,'Max',3,'Value',1,...
    'Position',[120 20 150 20],...
    'Callback',@changeSpeed);

% Inclination Slider
uicontrol('Style','slider',...
    'Min',0,'Max',90,'Value',45,...
    'Position',[300 20 150 20],...
    'Callback',@changeInclination);

% ================= ANIMATION LOOP =================
i = 1;
while ishandle(fig)

    if running
        set(sat,'XData',x_new(i),'YData',y_new(i),'ZData',z(i))
        drawnow

        pause(0.05 * (min(v)/v(i)) / speed_factor)

        i = i + 1;
        if i > length(x)
            i = 1;
        end
    else
        pause(0.1);
    end

end

% ================= CALLBACK FUNCTIONS =================

    function toggleRun(src,~)
        running = ~running;
        if running
            src.String = 'Pause';
        else
            src.String = 'Play';
        end
    end

    function changeSpeed(src,~)
        speed_factor = src.Value;
    end

    function changeInclination(src,~)
        inclination = src.Value;

        % Recalculate orbit
        y_new = y * cosd(inclination);
        z = y * sind(inclination);

        % Update orbit plot
        cla
        plot3(x_new, y_new, z, 'b','LineWidth',2)
        hold on
        surf(earth_r*Xs, earth_r*Ys, earth_r*Zs,...
            'FaceColor','k','EdgeColor','none')
        sat = plot3(x_new(i), y_new(i), z(i),...
            'ro','MarkerFaceColor','r','MarkerSize',6)

        axis equal
        grid on
        view(3)
    end

end